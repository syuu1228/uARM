EMSCRIPTEN_DIR=../..

all:
	$(EMSCRIPTEN_DIR)/emcc -O2 ../SoC.c ../CPU.c ../MMU.c ../mem.c ../callout_RAM.c ../RAM.c ../cp14.c ../cp15.c ../math64.c ../pxa255_IC.c ../pxa255_TIMR.c ../pxa255_RTC.c ../pxa255_UART.c ../pxa255_PwrClk.c ../pxa255_GPIO.c ../pxa255_DMA.c ../pxa255_DSP.c ../pxa255_LCD.c main_js.c ../icache.c ../dcache.c ../rt.c -I../ -o uARM.html --compression $(EMSCRIPTEN_DIR)/third_party/lzma.js/lzma-native,$(EMSCRIPTEN_DIR)/third_party/lzma.js/lzma-decoder.js,LZMA.decompress --preload-files rootfs.img -s TOTAL_MEMORY=33554432 -s ALLOW_MEMORY_GROWTH=0 -s ASM_JS=1
clean:
	rm -f uARM.html uARM.data uARM.data.compress uARM.js uARM.js.compress decompress.js
