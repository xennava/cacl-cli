#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>

template <typename T, size_t Size> struct Stack {
  T buffer[Size];
  unsigned int count;

  bool pop(T &v) {
    if (count == 0)
      return false;

    v = buffer[count];
    count--;
    return true;
  }
  bool push(const T v) {
    if (count == Size)
      return false;
    buffer[count] = v;
    count++;
    return true;
  }
  bool empty() { return count == 0; }
  bool full() { return count == Size; }
  size_t size() const { return Size; }
};

enum class TokenType : unsigned short {
  empty = 0,
  Float,
  Integer,
  NUMBER,
  Plus,
  Minus,
  Multiply,
  Divide,
  Equal,
  LParenth,
  RParenth,
  WHITESPACE,
  DOT,
  x,
  y,
  z
};

struct Token {
  TokenType type;
  unsigned short start = 0;
  unsigned short len = 0;
};

TokenType getTokenType(char &c) {
  using enum TokenType;
  if (c <= '9' && c >= '0') {
    return NUMBER;
  }
  switch (c) {
  case '.':
    return DOT;
    break;
  case '+':
    return Plus;
    break;
  case '-':
    return Minus;
    break;
  case '*':
    return Multiply;
    break;
  case '/':
  case ':':
    return Divide;
    break;
  case '(':
    return LParenth;
    break;
  case ')':
    return RParenth;
    break;
  case '=':
    return Equal;
    break;
  case 'x':
    return x;
    break;
  case 'y':
    return y;
    break;
  case 'z':
    return z;
    break;
  case ' ':
    return WHITESPACE;
  default:
    return empty;
    break;
  }
}

template <std::size_t N> void lexer(std::string &b, Stack<Token, N> &tokens) {
  using enum TokenType;

  Token t;
  TokenType next = empty, now = getTokenType(b[0]);
  bool save = true;
  bool atEnd = false;
  for (int i = 0; i < b.size(); i++) {
    atEnd = (i == b.size() - 1);
    t.type = now;

    char cb;
    if (!atEnd)
      cb = b[i + 1];

    next = getTokenType(cb);

    t.len++;

    if ((now == NUMBER || now == DOT) && next == NUMBER && !atEnd)
      save = false;
    else
      save = true;

    printf("%d: %d | save: %d | atEnd: %d\n", i, now, save, atEnd);

    now = next;

    if (save) {
      tokens.push(t);
      t.len = 0;
      t.start = i + 1;
      t.type = empty;
      save = true;
    }
  }
}
Stack<Token, 32> tokens;

int main(int argc, char *argv[]) {
  std::string expressionBuffer;
  std::getline(std::cin, expressionBuffer);

  lexer(expressionBuffer, tokens);

  for (int i = 0; i < tokens.count; i++) {
    printf("TokenType: %d   | start: %d | len: %d\n",
           static_cast<int>(tokens.buffer[i].type), tokens.buffer[i].start,
           tokens.buffer[i].len);
  }

  printf("\n%s", expressionBuffer.c_str());
  return 0;
}
