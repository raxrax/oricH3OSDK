; ---------------------------------------------------------------------------
; portions reused from:
; defence-force.org/public/oric/routines/keyboard/keyboard.s
; ---------------------------------------------------------------------------
#include <compat.h>
#include <via.h>
#include <keyboard.h>
; ---------------------------------------------------------------------------
.text

; ---------------------------------------------------------------------------
tmp_01    .byt 0
tmp_02    .byt 0
tmp_row   .byt 0

; ---------------------------------------------------------------------------
key_scan
          php
          sei
.(
          lda #$07
          sta tmp_01
next_row
          lda via_b
          and #$f8
          ora tmp_01
          sta via_b

          ldx tmp_01
          lda #$00
          sta key_bank,x

          lda #$01
          sta tmp_02
next_col
          lda #$0e
          sta via_aor

          ; Tell AY this is Register Number
          lda #$ef      ; ff
          ora _via_cb1_edge
          sta via_pcr

          ; Clear CB2, as keeping it high hangs on some orics.
          ; Pitty, as all this code could be run only once, otherwise
          ldy #$cd      ; dd
          ora _via_cb1_edge
          sty via_pcr

          lda #$ff
          eor tmp_02
          sta via_aor

          lda #$ed      ; fd
          ora _via_cb1_edge
          sta via_pcr
          lda #$cd      ; dd
          ora _via_cb1_edge
          sta via_pcr

          ldx tmp_01
          lda via_b
          and #$08
          beq nokey
          lda tmp_02
          ora key_bank,x
          sta key_bank,x
nokey
          asl tmp_02
          lda tmp_02
          bne next_col

          dec tmp_01
          bpl next_row
.)
          plp
          rts

_key_stat
          .dsb 1

tab_ascii
          .asc "7",      "n",       "5",        "v",        KEY_RCTRL,        "1",        "x",        "3"
          .asc "j",      "t",       "r",        "f",        0,                KEY_ESC,    "q",        "d"
          .asc "m",      "6",       "b",        "4",        KEY_LCTRL,        "z",        "2",        "c"
          .asc "k",      "9",       59,         "-",        0,                0,          92,         39
          .asc 32,       ",",       ".",        KEY_UP,     KEY_LSHIFT,       KEY_LEFT,   KEY_DOWN,   KEY_RIGHT
          .asc "u",      "i",       "o",        "p",        0,                KEY_DEL,    "]",        "["
          .asc "y",      "h",       "g",        "e",        KEY_FUNCT,        "a",        "s",        "w"
          .asc "8",      "l",       "0",        "/",        KEY_RSHIFT,       KEY_RETURN, "`",        "="

tab_ascii_hi
          .asc "&",      "N",       "%",        "V",        KEY_RCTRL,        "!",        "X",        "#"
          .asc "J",      "T",       "R",        "F",        0,                KEY_ESC,    "Q",        "D"
          .asc "M",      94,        "B",        "$",        KEY_LCTRL,        "Z",        "@",        "C"
          .asc "K",      "(",       ":",        "_",        0,                0,          "|",        34
          .asc 32,       "<",       ">",        KEY_UP,     KEY_LSHIFT,       KEY_LEFT,   KEY_DOWN,   KEY_RIGHT
          .asc "U",      "I",       "O",        "P",        0,                KEY_DEL,    "}",        "{"
          .asc "Y",      "H",       "G",        "E",        KEY_FUNCT,        "A",        "S",        "W"
          .asc "*",      "L",       ")",        "?",        KEY_RSHIFT,       KEY_RETURN, "~",        "+"

tab_st
          .byt KEY_RCTRL, $00, KEY_LCTRL, $00, KEY_LSHIFT, $00, KEY_FUNCT, KEY_RSHIFT

key_bank
          .dsb 8
old_key
          .byt 0

; Reads a key (single press, but repeating)
; Returns: X = ctrl/shift/funct status
;          A = ASCII value
key_getcharstat
.(
          ; Proceed ctrl/shift/funct keys
          lda #$00
          sta _key_stat
          ldx #$07
loopst
          lda key_bank,x
          and #$10
          beq skipst
          lda tab_st,x
          ora _key_stat
          sta _key_stat
skipst
          dex
          bpl loopst

          ldx #$07
loop
          lda key_bank,x
          and #$ef
          beq skip

          ldy #$ff
loop2
          iny
          lsr
          bcc loop2
          txa
          asl
          asl
          asl
          sty tmp_row
          clc
          adc tmp_row
          tax
          lda _key_stat
          and #KEY_SHIFT
          beq getcode
          txa
          clc
          adc #$40
          tax
getcode
          lda tab_ascii,x
          ldx _key_stat
          rts
skip
          dex
          bpl loop
          tax
          rts
.)

; Read a single key no repeating.
; Returns: X = ASCII value
;          A = ctrl/shift/funct status
_key_getc
.(
          jsr key_scan
          jsr key_getcharstat

          tay
          txa
          and #KEY_CTRL
          beq noctrl
          tya
          cmp #"a"-1
          bmi noctrl
          cmp #"z"+1
          bpl noctrl
          sec
          sbc #"a"-1
          tay
noctrl
          cpy old_key
          bne ret
          return(0)
ret
          sty old_key
          retbyt(old_key)
.)

; Read a single key repeating.
; Returns: X = ASCII value
;          A = ctrl/shift/funct status
_key_scanc
.(
          jsr key_scan
          jsr key_getcharstat

          tay
          txa
          and #KEY_CTRL
          beq noctrl
          tya
          cmp #"a"-1
          bmi noctrl
          cmp #"z"+1
          bpl noctrl
          sec
          sbc #"a"-1
          tay
noctrl
          sty old_key
          retbyt(old_key)
.)


; ; ------------------------------------------------------------------
; Routine to check for particular key
; ; ------------------------------------------------------------------
; ;  Key required                Accumulator               X register
; ; ------------------------------------------------------------------
; ;  1 2 3                       0 2 0                     DF BF 7F
; ;  4 5 6                       2 0 2                     F7 FB FD
; ;  7 8 9                       0 7 3                     FE FE FD
; ;  0 -=                        7 3 7                     FB F7 7F
; ;  \ ESC Q                     3 1 1                     BF DF BF
; ;  W E R                       6 6 1                     7F F7 FB
; ;  T Y U                       1 6 5                     FD FE FE
; ;  I 0 P                       5 5 5                     FD FB F7
; ;  [ ] DEL                     5 5 5                     7F BF DF
; ;  CTRL A S                    2 6 6                     EF DF BF
; ;  D F G                       1 1 6                     7F F7 FB
; ;  H J K                       6 1 3                     FD FE FE
; ;  L ; “                       7 3 3                     FD FB 7F
; ;  RETURN                      7                         DF
; ;  SHIFT (LEFT)                4                         EF
; ;  Z X C                       2 0 2                     DF BF 7F
; ;  VBN                         0 2 0                     F7 FB FD
; ;  M comma period              2 4 4                     FE FD FB
; ;  / SHIFT (RIGHT)             7 7                       F7 EF
; ;  LEFT ARROW                  4                         DF
; ;  DOWN ARROW                  4                         BF
; ;  SPACE                       4                         FE
; ;  UP ARROW                    4                         F7
; ;  RIGHT ARROW                 4                         7F
; 
; ; ------------------------------------------------------------------
; 
;         php
;         sei
;         pha
;         lda     #$0e
;         jsr     $f590 ; ROM1.0 $f535
;         pla
;         ora     #$b8
;         sta     $0300
;         ldx     #$04
; delay   dex     
;         bne     delay
;         lda     $0300
;         and     #$08
;         tax
;         plp
;         txa
;         rts
