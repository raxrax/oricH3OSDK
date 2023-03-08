

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



