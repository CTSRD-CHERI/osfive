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

#ifndef	_DEV_DISPLAY_DSI_H_
#define	_DEV_DISPLAY_DSI_H_

#define	DSI_GEN_SHORT_WRITE_P0	0x03 /* Generic short write, no parameters */
#define	DSI_GEN_SHORT_WRITE_P1	0x13 /* Generic short write, one parameter */
#define	DSI_DCS_SHORT_WRITE_P0	0x05 /* DCS short write, no parameters */
#define	DSI_DCS_SHORT_WRITE_P1	0x15 /* DCS short write, one parameter */
#define	DSI_GEN_SHORT_WRITE_P2	0x23 /* Generic short write, two parameters */
#define	DSI_GEN_LONG_WRITE	0x29 /* Generic long write */
#define	DSI_DCS_LONG_WRITE	0x39 /* DCS long write */
#define	DSI_GEN_READ_P0		0x04 /* Generic read, no parameters */
#define	DSI_GEN_READ_P1		0x14 /* Generic read, one parameter */
#define	DSI_GEN_READ_P2		0x24 /* Generic read, two parameters */
#define	DSI_DCS_READ_P0		0x06 /* DCS read, no parameters */
#define	DSI_MAX_RET_PKT_SIZE	0x37 /* Set maximum return packet size */

#define	DSI_PP_STREAM_18	0x1e /* 18-bit RGB-666 packed pixel stream */
#define	DSI_LPP_STREAM_18	0x2e /* 18-bit RGB-666 loosely packed */
#define	DSI_PP_STREAM_24	0x3e /* 24-bit RGB-888 packed pixel stream */

struct dsi_device {
	void (*dsi_short)(struct dsi_device *, uint8_t vchid, uint8_t data_type,
	    uint8_t data0, uint8_t data1);
	void (*dsi_long)(struct dsi_device *, uint8_t vchid, uint32_t data_type,
	    const uint8_t *params, uint32_t nparams);
	void *arg;
	uint8_t vchid;
};

typedef struct dsi_device dsi_device_t;

#endif /* !_DEV_DISPLAY_DSI_H_ */
