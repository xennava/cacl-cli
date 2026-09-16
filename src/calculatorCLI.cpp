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

enum class TokenType {
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
  unsigned int start = 0;
  unsigned int len = 0;
};

template <std::size_t N> void lexer(std::string &b, Stack<Token, N> &tokens) {
  using enum TokenType;

  Token t;
  TokenType prev = empty, next = empty;
  bool isTokenChanged = false;
  bool save = false;
  for (int i = 0; i < b.size(); i++) {
    prev = next;

    char &c = b[i];
    if (c <= '9' && c >= '0') {
      t.type = Integer;
    }

    switch (c) {
    case '.':
      t.type = DOT;
      break;
    case '+':
      t.type = Plus;
      break;
    case '-':
      t.type = Minus;
      break;
    case '*':
      t.type = Multiply;
      break;
    case '/':
    case ':':
      t.type = Divide;
      break;
    case '(':
      t.type = LParenth;
      break;
    case ')':
      t.type = RParenth;
      break;
    case '=':
      t.type = Equal;
      break;
    case 'x':
      t.type = x;
      break;
    case 'y':
      t.type = y;
      break;
    case 'z':
      t.type = z;
      break;
    case ' ':
      t.type = WHITESPACE;
    default:
      break;
    }

    next = t.type;
    isTokenChanged = (next != prev);

    if (t.type == Integer || t.type == Float ||
        ((prev == Integer || prev == Float) && t.type == DOT))
      t.len++;
    else {
      t.len = 1;
    }

    if (isTokenChanged || b[i + 1] == ' ') {
      save = true;
    }

    if (save)
      tokens.push(t);
  }
}
Stack<Token, 32> tokens;

int main(int argc, char *argv[]) {
  std::string expressionBuffer;
  std::getline(std::cin, expressionBuffer);

  lexer(expressionBuffer, tokens);

  for (int i = 0; i < tokens.count; i++) {
    printf("TokenType: %d | start: %d | len: %d\n",
           static_cast<int>(tokens.buffer[i].type), tokens.buffer[i].start,
           tokens.buffer[i].len);
  }

  printf("\n%s", expressionBuffer.c_str());
  return 0;
}
