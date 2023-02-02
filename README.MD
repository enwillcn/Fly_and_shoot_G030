# Port the fly and shoot game to STM32G030K6Tx
1. Use SPI + DMA for 1.3' oled display
2. Use TIM3 instead of systick as the system tick clock, the button detection function is within TIM3 ISR callback.
3. In bsp.c use `uint32_t l_fb[BSP_SCREEN_HEIGHT + 1][BSP_SCREEN_WIDTH / 32U]` as display buffer.
   To work with oled.c library and spi+dma, need to transfer the original buffer data into buffer `uint8_t OLED_GRAM[8][132]`, refer to `void OLED_Refresh_SPI(void)`