#include <ThisFunc/Disassembler.hpp>

void ThisFunc::VM::disassemble (const Chunk& chunk) {
  std::cout << "==========" << chunk.address ( ) << "==========" << std::endl;

  for (u32 offset = 0; offset < chunk.getSize ( );) {
    offset = instruction (chunk, offset);
  }

  std::cout << "==========" << chunk.address ( ) << "==========" << std::endl;
}

u32 ThisFunc::VM::instruction (const Chunk& chunk, u32 offset) {
  char buffer[8];
  snprintf (buffer, 7, "%04d ", offset);
  buffer[7] = '\0';

  std::cout << buffer;

  if (offset > 0 && chunk (offset).line == chunk (offset - 1).line) {
    std::cout << "   |";
  } else {
    snprintf (buffer, 7, "%4d", chunk (offset).line);
    buffer[7] = '\0';
    std::cout << buffer;
  }

  snprintf (buffer, 7, "%d ", chunk (offset).column);
  buffer[7] = '\0';

  std::cout << ":" << buffer;

  switch (chunk[offset]) {
    case OP_RETURN: return simple ("RETURN", offset);
    case OP_CONSTANT: return constant ("CONSTANT", chunk, offset);
    case OP_CALL: return call ("CALL", chunk, offset);
    case OP_LOAD: return call ("LOAD", chunk, offset);
    case OP_BIND_NUMBER: return simple ("BIND NUMBER", offset);
    case OP_ADD: return simple ("ADD", offset);
    case OP_SUBTRACT: return simple ("SUBTRACT", offset);
    case OP_MULTIPLY: return simple ("MULTIPLY", offset);
    case OP_DIVIDE: return simple ("DIVIDE", offset);
    case OP_PRINT: return simple ("PRINT", offset);
    case OP_SIN: return simple ("SIN", offset);
    case OP_LIST: return call ("LIST", chunk, offset);
    case OP_MAP: return simple ("MAP", offset);
    case OP_JZ: return jump ("JUMP IF ZERO", chunk, offset);
    case OP_JMP: return jump ("JUMP", chunk, offset);
    case OP_POP: return simple ("POP", offset);
    case OP_POW: return simple ("POW", offset);
    case OP_LE: return simple ("LE", offset);
    case OP_HEAD: return simple ("HEAD", offset);
    case OP_SQRT: return simple ("SQRT", offset);
    case OP_COS: return simple ("COS", offset);
    case OP_EQ: return simple ("EQ", offset);
    case OP_NAND: return simple ("NAND", offset);
    case OP_TAIL: return simple ("TAIL", offset);
    case NOOP:
      return simple ("NOOP", offset);
defaut:
      std::cout << "Unknown OpCode " << (u32) chunk[offset] << std::endl;
      return offset + 1;
  }
  return offset + 1;
}

u32 ThisFunc::VM::simple (const std::string& name, u32 offset) {
  std::cout << name << std::endl;
  return offset + 1;
}

u32 ThisFunc::VM::jump (const std::string& name,
                        const Chunk&       chunk,
                        u32                offset) {
  std::cout << name << " ";
  char buf[16];
  snprintf (buf,
            15,
            "%02d%02d",
            (u32) chunk[offset + 1],
            (u32) chunk[offset + 2]);
  std::cout << buf << std::endl;
  return offset + 3;
}

u32 ThisFunc::VM::constant (const std::string& name,
                            const Chunk&       chunk,
                            u32                offset) {
  Byte constantIdx = chunk[offset + 1];
  std::cout << name << " " << (u32) constantIdx << " ";
  value (chunk.getConstant (constantIdx));
  std::cout << std::endl;
  return offset + 2;
}

u32 ThisFunc::VM::call (const std::string& name,
                        const Chunk&       chunk,
                        u32                offset) {
  Byte idx = chunk[offset + 1];
  std::cout << name << " " << (u32) idx;
  std::cout << std::endl;
  return offset + 2;
}

void ThisFunc::VM::value (Constant c) { std::cout << c; }
