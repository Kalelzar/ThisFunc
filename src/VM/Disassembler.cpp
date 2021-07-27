#include <ThisFunc/Disassembler.hpp>

void ThisFunc::VM::disassemble(const Chunk &chunk) {

  std::cout << "==========" << chunk.address() << "==========" << std::endl;

  for (u32 offset = 0; offset < chunk.getSize();) {
    offset = instruction(chunk, offset);
  }

  std::cout << "==========" << chunk.address() << "==========" << std::endl;
}

u32 ThisFunc::VM::instruction(const Chunk &chunk, u32 offset) {

  char buffer[8];
  snprintf(buffer, 7, "%04d ", offset);
  buffer[7] = '\0';

  std::cout << buffer;

  if (offset > 0 && chunk(offset).line == chunk(offset - 1).line) {
    std::cout << "   |";
  } else {
    snprintf(buffer, 7, "%4d", chunk(offset).line);
    buffer[7] = '\0';
    std::cout << buffer;
  }

  snprintf(buffer, 7, "%d ", chunk(offset).column);
  buffer[7] = '\0';

  std::cout << ":" << buffer;

  switch (chunk[offset]) {
  case OP_RETURN:
    return simple("RETURN", offset);
  case OP_CONSTANT:
    return constant("CONSTANT", chunk, offset);
  case OP_ADD:
    return simple("ADD", offset);
  case OP_SUBTRACT:
    return simple("SUBTRACT", offset);
  case OP_MULTIPLY:
    return simple("MULTIPLY", offset);
  case OP_DIVIDE:
    return simple("DIVIDE", offset);
  case OP_PRINT:
    return simple("PRINT", offset);
  case NOOP:
    return simple("NOOP", offset);
  defaut:
    std::cout << "Unknown OpCode " << (u32)chunk[offset] << std::endl;
    return offset + 1;
  }
  return offset + 1;
}

u32 ThisFunc::VM::simple(const std::string &name, u32 offset) {
  std::cout << name << std::endl;
  return offset + 1;
}

u32 ThisFunc::VM::constant(const std::string &name, const Chunk &chunk,
                           u32 offset) {
  Byte constantIdx = chunk[offset + 1];
  std::cout << name << " " << (u32)constantIdx << " ";
  value(chunk.getConstant(constantIdx));
  std::cout << std::endl;
  return offset + 2;
}

void ThisFunc::VM::value(Constant c) { std::cout << c; }
