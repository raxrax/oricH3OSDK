
;; #ifdef SAVE_ZERO_PAGE
#define OPCODE_DEC_ZERO $CE
#define OPCODE_INC_ZERO $EE
;; #else
;; #define OPCODE_DEC_ZERO $C6
;; #define OPCODE_INC_ZERO $E6
;; #endif

;; void h3_curset()
_h3_curset:
.(
;;    h3OffsetX = h3TabCalcOffset[h3X];
    ldy     _h3X
    lda     _h3TabCalcOffset,y 
    sta     _h3OffsetX

;;    h3Addr = h3MapX[h3X] + h3Y;
    tya
    asl
    tay
    lda     _h3MapX,y 
    iny
    clc 
    adc     _h3Y
    sta     tmp0
    lda     _h3MapX,y 
    adc     #0
    sta     tmp0+1

;;    switch (h3fb)
    lda _h3fb
    bne case_1
;;    {
;;    case 0:
;;        // poke(h3Addr, peek(h3Addr) & ~h3OffsetX);
;;        *((unsigned char*)h3Addr) &= ~h3OffsetX;
        ldy     #0
        lda     (tmp0),y 
        and     _h3OffsetX
        sta     (tmp0),y
;;        break;
        rts
;;
case_1:
    cmp     #1
    bne     case_2
;;    case 1:
;;        // poke(h3Addr, peek(h3Addr) | h3OffsetX);
;;        *((unsigned char*)h3Addr) |= h3OffsetX;
        ldy     #0
        lda     (tmp0),y 
        ora     _h3OffsetX
        sta     (tmp0),y
;;        break;
        rts
;;
case_2:
    cmp     #2
    bne     h3_curset_done
;;    case 2:
;;        // poke(h3Addr, peek(h3Addr) ^ h3OffsetX);
;;        *((unsigned char*)h3Addr) ^= h3OffsetX;
        ldy     #0
        lda     (tmp0),y 
        eor     _h3OffsetX
        sta     (tmp0),y
;;        break;
        rts
;;    }
h3_curset_done
.)
    rts

_h3P1X .byt 0
_h3P1Y .byt 0
_h3P2X .byt 0
_h3P2Y .byt 0

_h3A1X .dsb 1
_h3A1Y .dsb 1
_h3A1destX .dsb 1
_h3A1destY .dsb 1
_h3A1dX .dsb 1
_h3A1dY .dsb 1
_h3A1err .dsb 1
_h3A1sX .dsb 1
_h3A1sY .dsb 1
_h3A1arrived .dsb 1


_h3DrawLine:
.(
;;     A1X     = P1X;
	lda 	_h3P1X
	sta		_h3A1X
;;     A1Y     = P1Y;
	lda 	_h3P1Y
	sta		_h3A1Y
;;     A1destX = P2X;
	lda 	_h3P2X
	sta		_h3A1destX
;;     A1destY = P2Y;
	lda 	_h3P2Y
	sta		_h3A1destY
;;     A1dX    = abs(P2X - P1X);
;;     A1sX    = P1X < P2X ? 1 : -1;
; a = P1X-P2X
    sec
    lda _h3P1X
    sbc _h3P2X
; if a >= 0 :
    bmi h3DrawLine_h3P2Xoverp1x
;   dx = a
    sta _h3A1dX
;   sx = -1
    lda #$FF
    sta _h3A1sX
    lda #OPCODE_DEC_ZERO
    sta patch_h3DrawLine_incdec_h3A1X
    jmp h3DrawLine_computeDy
; else
h3DrawLine_h3P2Xoverp1x:
;   dx = -a
    eor #$FF
    sec
    adc #$00
    sta _h3A1dX
;   sx =1
    lda #$01
    sta _h3A1sX
    lda #OPCODE_INC_ZERO
    sta patch_h3DrawLine_incdec_h3A1X
; endif


h3DrawLine_computeDy:
;;     A1dY    = -abs(P2Y - P1Y);
;;     A1sY    = P1Y < P2Y ? 1 : -1;
; a = P1Y-P2Y
    lda _h3P1Y
    sec
    sbc _h3P2Y
; if a >= 0 :
    bmi h3DrawLine_h3P2Yoverp1y
;   dy = -a
    eor #$FF
    sec
    adc #$00
    sta _h3A1dY
;   sy = -1
    lda #$FF
    sta _h3A1sY
    lda #OPCODE_DEC_ZERO
    sta patch_h3DrawLine_incdec_h3A1Y
    jmp h3DrawLine_computeErr
; else
h3DrawLine_h3P2Yoverp1y:
;   dy = a
    sta _h3A1dY
;   sy = 1
    lda #$01
    sta _h3A1sY
    lda #OPCODE_INC_ZERO
    sta patch_h3DrawLine_incdec_h3A1Y
; endif


h3DrawLine_computeErr:
;;     A1err   = A1dX + A1dY;
; a = A1dX
    lda		_h3A1dX
; a = a + dy
    clc
    adc		_h3A1dY
; err = a
    sta		_h3A1err

;;     if ((A1err > 64) || (A1err < -63)) return;
    sec
    sbc #$40
    .(:bvc skip : eor #$80: skip:.)
    bmi h3DrawLine_goon01
	jmp h3DrawLine_endloop
h3DrawLine_goon01:
    lda _h3A1err
    sec
    sbc #$C0
    .(:bvc skip : eor #$80: skip:.)
    bpl h3DrawLine_goon02:
	jmp h3DrawLine_endloop
h3DrawLine_goon02:


;;     while (1) {  ;; loop
h3DrawLine_loop:

;;         ;;printf ("plot [%d, %d] %d %d\n", _h3A1X, _h3A1Y, distseg, ch2disp);get ();          

        ;; if ((A1Y >= 0) && (A1Y < MAX_Y) && (A1X >= 0) && (A1X < MAX_X))
            lda _h3A1X : sta _h3X :
            lda _h3A1Y : sta _h3Y :
            jsr _h3_curset
skipOutOfBoundPixel:
;;         if ((A1X == A1destX) && (A1Y == A1destY)) break;
;       a = A1X
        lda _h3A1X
;       if a != A1destX goto continue
        cmp _h3A1destX
        bne h3DrawLine_continue
;       a = A1Y
        lda _h3A1Y
;       if a != A1destY goto continue
        cmp _h3A1destY
        bne h3DrawLine_continue
;       goto endloop
        jmp h3DrawLine_endloop
;continue:
h3DrawLine_continue:

;;      e2 = 2*A1err;
;;         e2 = (A1err < 0) ? (
;;                 ((A1err & 0x40) == 0) ? (
;;                                                 0x80)
;;                                         : (
;;                                             A1err << 1))
;;             : (
;;                 ((A1err & 0x40) != 0) ? (
;;                                                 0x7F)
;;                                         : (
;;                                                 A1err << 1));
		lda _h3A1err
		bpl h3DrawLine_errpositiv_01
		asl
		bmi h3DrawLine_errdone_01
		lda #$80
		jmp h3DrawLine_errdone_01
	
h3DrawLine_errpositiv_01:	
		asl
		bpl h3DrawLine_errdone_01
		lda #$7F
h3DrawLine_errdone_01:	
		sta reg4

;;         if (e2 >= A1dY) {
        sec
        sbc _h3A1dY
        .(:bvc skip : eor #$80: skip:.)
        bmi h3DrawLine_dyovera

;;             A1err += A1dY;  ;; e_xy+e_x > 0
			lda _h3A1err
			clc
			adc _h3A1dY
			sta _h3A1err
;;             A1X += A1sX;
patch_h3DrawLine_incdec_h3A1X:
            inc _h3A1X
			; lda _h3A1X
			; clc
			; adc _h3A1sX
			; sta _h3A1X
h3DrawLine_dyovera:
;;         }
;;         if (e2 <= A1dX) {  ;; e_xy+e_y < 0
		lda _h3A1dX
		sec
		sbc reg4
		.(:bvc skip : eor #$80: skip:.)
		bmi h3DrawLine_e2overdx
;;             A1err += A1dX;
			lda _h3A1err
			clc
			adc _h3A1dX
			sta _h3A1err
;;             A1Y += A1sY;
patch_h3DrawLine_incdec_h3A1Y:
            inc _h3A1Y
			; lda _h3A1Y
			; clc
			; adc _h3A1sY
			; sta _h3A1Y
h3DrawLine_e2overdx
;;         }
	jmp h3DrawLine_loop
;;     }


h3DrawLine_endloop:
h3DrawLine_done:

.) 
    rts
;; _A1Right .dsb 1