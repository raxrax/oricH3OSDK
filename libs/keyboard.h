#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#define KEY_UP          1
#define KEY_LEFT        2
#define KEY_DOWN        3
#define KEY_RIGHT       4

#define KEY_LCTRL       1
#define KEY_RCTRL       2
#define KEY_CTRL        (KEY_LCTRL|KEY_RCTRL)

#define KEY_LSHIFT      4
#define KEY_RSHIFT      8
#define KEY_SHIFT       (KEY_LSHIFT|KEY_RSHIFT)

#define KEY_FUNCT       16

/* This keys do have ASCII values, lets use them */

#define KEY_SPACE      32
#define KEY_BACKSPACE   8
#define KEY_RETURN     13
#define KEY_ESC        27
#define KEY_DEL       127

#ifdef ASSEMBLER
#else

extern char key_stat;

int key_getc(void);
int key_scanc(void);

#endif /* ASSEMBLER */

#endif /* __KEYBOARD_H__ */
