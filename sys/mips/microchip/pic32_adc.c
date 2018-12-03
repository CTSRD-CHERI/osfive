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
#include <sys/systm.h>

#include <mips/microchip/pic32_adc.h>

#define	RD4(_sc, _reg)		*(volatile uint32_t *)((_sc)->base + _reg)
#define	WR4(_sc, _reg, _val)	*(volatile uint32_t *)((_sc)->base + _reg) = _val
#define	RD2(_sc, _reg)		*(volatile uint16_t *)((_sc)->base + _reg)
#define	WR2(_sc, _reg, _val)	*(volatile uint16_t *)((_sc)->base + _reg) = _val
#define	RD1(_sc, _reg)		*(volatile uint8_t *)((_sc)->base + _reg)
#define	WR1(_sc, _reg, _val)	*(volatile uint8_t *)((_sc)->base + _reg) = _val

uint32_t
pic32_adc_convert(struct pic32_adc_softc *sc, int channel)
{
	uint32_t reg;
	uint32_t val;

	WR4(sc, ADCHS, (1 << channel));

	reg = ADCON2_BUFREGEN;
	reg |= ADCON2_CSCNA;
	WR4(sc, ADCON2, reg);

	/* TODO: unmagic */
	WR4(sc, ADCON3, 0x402);
	WR4(sc, ADCHIT, 0);

	reg = (ADCON1_MODE12 | ADCON1_FORM_I32);
	WR4(sc, ADCON1, reg);

	reg = RD4(sc, ADCON1);
	reg |= ADCON1_ON;
	WR4(sc, ADCON1, reg);

	/* Start */
	reg = RD4(sc, ADCON1);
	reg |= ADCON1_SAMP;
	WR4(sc, ADCON1, reg);

	udelay(100);

	reg = RD4(sc, ADCON1);
	reg &= ~ADCON1_SAMP;
	WR4(sc, ADCON1, reg);

	while ((RD4(sc, ADCON1) & ADCON1_DONE) == 0)
		;

	val = RD4(sc, ADCBUF(channel));

	WR4(sc, ADCON1, 0);

	return (val);
}

void
pic32_adc_init(struct pic32_adc_softc *sc,
    uint32_t base)
{

	sc->base = base;
}
