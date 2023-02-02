/* USER CODE BEGIN Header */
/**
        ******************************************************************************
        * @file           : main.c
        * @brief          : Main program body
        ******************************************************************************
        * @attention
        *
        * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
        * All rights reserved.</center></h2>
        *
        * This software component is licensed by ST under BSD 3-Clause license,
        * the "License"; You may not use this file except in compliance with the
        * License. You may obtain a copy of the License at:
        *                        opensource.org/licenses/BSD-3-Clause
        *
        ******************************************************************************
        */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "string.h"
#include "stdio.h"
#include "qpc.h"
#include "bsp.h"
#include "game.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
Q_DEFINE_THIS_FILE

static QTicker l_ticker0; /* ticker active object for tick rate 0 */
QActive *the_Ticker0 = &l_ticker0.super;
/* USER CODE END 0 */

/**
    * @brief  The application entry point.
    * @retval int
    */
int main(void)
{
    /* USER CODE BEGIN 1 */
    QF_init();  /* initialize the framework and the underlying RT kernel */
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_SPI2_Init();
    MX_TIM3_Init();
    /* USER CODE BEGIN 2 */

	OLED_Init();

    static QEvt const * missileQueueSto[2];
    static QEvt const * shipQueueSto[3];
    static QEvt const * tunnelQueueSto[GAME_MINES_MAX + 5];

    static QF_MPOOL_EL(QEvt)           smlPoolSto[10];
    static QF_MPOOL_EL(ObjectImageEvt) medPoolSto[2*GAME_MINES_MAX + 10];

    static QSubscrList    subscrSto[MAX_PUB_SIG];

    //QF_init();  /* initialize the framework and the underlying RT kernel */
    BSP_init(); /* initialize the Board Support Package */


	/* init publish-subscribe... */
	QF_psInit(subscrSto, Q_DIM(subscrSto));

	/* initialize the event pools... */
	QF_poolInit(smlPoolSto, sizeof(smlPoolSto), sizeof(smlPoolSto[0]));
	QF_poolInit(medPoolSto, sizeof(medPoolSto), sizeof(medPoolSto[0]));

    /* object dictionaries for AOs... */
    QS_OBJ_DICTIONARY(AO_Missile);
    QS_OBJ_DICTIONARY(AO_Ship);
    QS_OBJ_DICTIONARY(AO_Tunnel);

    /* signal dictionaries for globally published events... */
    QS_SIG_DICTIONARY(TIME_TICK_SIG,      (void *)0);
    QS_SIG_DICTIONARY(PLAYER_TRIGGER_SIG, (void *)0);
    QS_SIG_DICTIONARY(PLAYER_QUIT_SIG,    (void *)0);
    QS_SIG_DICTIONARY(GAME_OVER_SIG,      (void *)0);
  
  
  
    /* start the active objects... */
    QTicker_ctor(&l_ticker0, 0U); /* active object for tick rate 0 */
    QACTIVE_START(the_Ticker0,
                                1U,                /* QP priority */
                                0, 0, 0, 0, 0);    /* no queue, no stack , no init. event */
    Tunnel_ctor_call();
    QACTIVE_START(AO_Tunnel,
                                2U,                /* QP priority */
                                tunnelQueueSto,  Q_DIM(tunnelQueueSto), /* evt queue */
                                (void *)0, 0U,     /* no per-thread stack */
                                (QEvt *)0);        /* no initialization event */
    Ship_ctor_call();
    QACTIVE_START(AO_Ship,
                                3U,                /* QP priority */
                                shipQueueSto,    Q_DIM(shipQueueSto), /* evt queue */
                                (void *)0, 0U,     /* no per-thread stack */
                                (QEvt *)0);        /* no initialization event */
    Missile_ctor_call();
    QACTIVE_START(AO_Missile,
                                4U,                /* QP priority */
                                missileQueueSto, Q_DIM(missileQueueSto), /* evt queue */
                                (void *)0, 0U,     /* no per-thread stack */
                                (QEvt *)0);        /* no initialization event */

    return QF_run(); /* run the QF application */
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
        while (1)
        {
        
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        }
    /* USER CODE END 3 */
}

/**
    * @brief System Clock Configuration
    * @retval None
    */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
    RCC_OscInitStruct.PLL.PLLN = 8;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                                            |RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
    * @brief  This function is executed in case of error occurrence.
    * @retval None
    */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
        /* User can add his own implementation to report the HAL error return state */
        __disable_irq();
        while (1)
        {
        }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
    * @brief  Reports the name of the source file and the source line number
    *         where the assert_param error has occurred.
    * @param  file: pointer to the source file name
    * @param  line: assert_param error line source number
    * @retval None
    */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
        /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
