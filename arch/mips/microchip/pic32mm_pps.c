/*-
 * Copyright (c) 2018 Ruslan Bukin <br@bsdpad.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/types.h>
#include <mips/microchip/pic32mm_pps.h>

#define	RD4(_sc, _reg)		\
	*(volatile uint32_t *)((_sc)->base + _reg)
#define	WR4(_sc, _reg, _val)	\
	*(volatile uint32_t *)((_sc)->base + _reg) = _val

static void
pic32_pps_unlock(struct pic32_pps_softc *sc)
{
	uint32_t reg;

	*(volatile uint32_t *)(SYSKEY) = 0xAA996655;
	*(volatile uint32_t *)(SYSKEY) = 0x556699AA;

	reg = RD4(sc, PPS_RPCON);
	reg &= ~(1 << 11);
	WR4(sc,	PPS_RPCON, reg);
}

void
pic32_pps_rpinr(struct pic32_pps_softc *sc,
    uint32_t reg, uint32_t val)
{

	WR4(sc,	PPS_RPINR(reg), val);
}

void
pic32_pps_rpor(struct pic32_pps_softc *sc,
    uint8_t rpor, uint32_t val)
{
	uint32_t reg;

	reg = RD4(sc, PPS_RPOR(rpor));
	reg |= val;
	WR4(sc, PPS_RPOR(rpor), reg);
}

void
pic32_pps_init(struct pic32_pps_softc *sc,
    uint32_t base)
{

	sc->base = base;

	pic32_pps_unlock(sc);
}
