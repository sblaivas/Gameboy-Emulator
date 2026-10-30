gb.h:
This file is the public interface to the emulator where it lists what code outside the core is allowed to do with a Game Boy, without exposing how the Game Boy works inside. 

There are five functions that will be used:
gb_create will turn on a Game Boy with a ROM
gb_destroy will turn it off and free its memory
gb_run_frame will run one frame of emulation
gb_framebuffer will get the current screen image
gb_set_buttons will tell it which buttons are pressed