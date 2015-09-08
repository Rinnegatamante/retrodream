#include "aica/aica.h"
#include "emu/dreamcast.h"

using namespace dreavm::aica;
using namespace dreavm::emu;
using namespace dreavm::holly;

AICA::AICA(Dreamcast *dc) : dc_(dc) {}

void AICA::Init() {
  aica_regs_ = dc_->aica_regs();
  wave_ram_ = dc_->wave_ram();
}

uint32_t AICA::Execute(uint32_t cycles) {
  // uint16_t MCIEB = *reinterpret_cast<uint16_t *>(&aica_regs_[MCIEB_OFFSET]);
  // uint16_t MCIPD = *reinterpret_cast<uint16_t *>(&aica_regs_[MCIPD_OFFSET]);

  // if (MCIEB || MCIPD) {
  //   LOG_INFO("0x%x & 0x%x", MCIEB, MCIPD);
  // }
  // dc_->holly()->RequestInterrupt(HOLLY_INTC_G2AICINT);

  return cycles;
}

uint32_t AICA::ReadRegister32(uint32_t addr) {
  // LOG_INFO("AICA::ReadRegister32 0x%x", addr);
  return *reinterpret_cast<uint32_t *>(&aica_regs_[addr]);
}

void AICA::WriteRegister32(uint32_t addr, uint32_t value) {
  // LOG_INFO("AICA::WriteRegister32 0x%x", addr);
  *reinterpret_cast<uint32_t *>(&aica_regs_[addr]) = value;
}

uint32_t AICA::ReadWave32(uint32_t addr) {
  // FIXME temp hack for unsupported audio regs hanging in Crazy Taxi 2
  if (addr == 0x5c) {
    return 0x54494e49;
  }

  return *reinterpret_cast<uint32_t *>(&wave_ram_[addr]);
}

void AICA::WriteWave32(uint32_t addr, uint32_t value) {
  *reinterpret_cast<uint32_t *>(&wave_ram_[addr]) = value;
}