/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <uxr/client/transport.h>
#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>
#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/string.h>
#include <geometry_msgs/msg/twist.h>
#include "usart.h"
// カスタムメッセージのインクルード
#include <custom_test_msgs/srv/add_three_ints.h>
#include <drive_msgs/msg/diff_drive.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// エラーハンドリングのためのマクロを設定
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printf("Failed status on line %d: %d. Aborting.\n",__LINE__,(int)temp_rc);}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printf("Failed status on line %d: %d. Continuing.\n",__LINE__,(int)temp_rc);}}

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
// サービスのリクエストとレスポンスの構造体を定義
custom_test_msgs__srv__AddThreeInts_Request req;
custom_test_msgs__srv__AddThreeInts_Response res;
geometry_msgs__msg__Twist sub;
std_msgs__msg__String pub;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
rcl_publisher_t publisher;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 3000 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
bool cubemx_transport_open(struct uxrCustomTransport * transport);
bool cubemx_transport_close(struct uxrCustomTransport * transport);
size_t cubemx_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err);
size_t cubemx_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);
void * microros_allocate(size_t size, void * state);
void microros_deallocate(void * pointer, void * state);
void * microros_reallocate(void * pointer, size_t size, void * state);
void * microros_zero_allocate(size_t number_of_elements, size_t size_of_element, void * state);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
// サービスのコールバック関数を定義
void service_callback(const void *request, void *response)
{
	// リクエストとレスポンスを適切な型にキャスト
	custom_test_msgs__srv__AddThreeInts_Request *_req = (custom_test_msgs__srv__AddThreeInts_Request *)request;
	custom_test_msgs__srv__AddThreeInts_Response *_res = (custom_test_msgs__srv__AddThreeInts_Response *)response;
	// 1秒スリープ（重い処理の代わり）
	osDelay(1000);
	// レスポンスに合計値をセット
	_res->sum = _req->a + _req->b + _req->c;
}

void subscription_callback(const void * msgin)
{
	 // Cast received message to used type
	  const drive_msgs__msg__DiffDrive * sub = (const drive_msgs__msg__DiffDrive *)msgin;

	  char hearing[] = "I'm hearing from f7";
	  rosidl_runtime_c__String__assignn(&pub.data, hearing, sizeof(hearing));

	  //データのpublish
	  RCSOFTCHECK(rcl_publish(&publisher, &pub, NULL));

	  HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET);
}
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  // micro-ROSの初期化
  	printf("start default task");
  	rmw_uros_set_custom_transport(
  	    true,
  	    (void *) &huart3,
  	    cubemx_transport_open,
  	    cubemx_transport_close,
  	    cubemx_transport_write,
  	    cubemx_transport_read);

  	rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();
  	freeRTOS_allocator.allocate = microros_allocate;
  	freeRTOS_allocator.deallocate = microros_deallocate;
  	freeRTOS_allocator.reallocate = microros_reallocate;
  	freeRTOS_allocator.zero_allocate =  microros_zero_allocate;
  	if (!rcutils_set_default_allocator(&freeRTOS_allocator)) {
  		printf("Error on default allocators (line %d)\n", __LINE__);
  	}

      // ここからサービスサーバの実装
  	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  	rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
  	rcl_allocator_t allocator = rcl_get_default_allocator();
  	rclc_support_t support;
  	rcl_node_t node = rcl_get_zero_initialized_node();
  	rcl_service_t service = rcl_get_zero_initialized_service();
  	publisher = rcl_get_zero_initialized_publisher();
  	rcl_subscription_t subscriber = rcl_get_zero_initialized_subscription();
  	rclc_executor_t executor = rclc_executor_get_zero_initialized_executor();
  	rcl_node_options_t node_ops = rcl_node_get_default_options();

  	RCCHECK(rcl_init_options_init(&init_options, allocator));
      // ROS_DOMAIN_IDの設定。
  	RCCHECK(rcl_init_options_set_domain_id(&init_options, 0));
  	rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator);
      // ノードの作成
  	RCCHECK(rclc_node_init_with_options(&node, "f7_node", "", &support, &node_ops));
      // サービスの作成
  	RCCHECK(rclc_service_init_default(&service, &node, ROSIDL_GET_SRV_TYPE_SUPPORT(custom_test_msgs, srv, AddThreeInts), "add_three_ints"));

  	 //publisherの作成
	RCCHECK(rclc_publisher_init_default(
	  &publisher,
	  &node,
	  ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
	  "/from_f767zi"));

	 //subscriberの作成
		RCCHECK(rclc_subscription_init_default(
		  &subscriber,
		  &node,
		  ROSIDL_GET_MSG_TYPE_SUPPORT(drive_msgs, msg, DiffDrive),
		  "/cmd_ras"));
      // エグゼキューターの作成。三番目の引数はextecuterに登録するコールバック関数の数。
  	RCCHECK(rclc_executor_init(&executor, &support.context, 2, &allocator));

      // エグゼキューターにサービスを追加
  	RCCHECK(rclc_executor_add_service(&executor, &service, &req, &res, &service_callback));
  	RCCHECK(rclc_executor_add_subscription(
  		  &executor, &subscriber, &sub,
  		  &subscription_callback, ON_NEW_DATA));

    //配列データを扱うときの処理
    rosidl_runtime_c__String__init(&pub);
    char hello[] = "Hello world from f7";
    rosidl_runtime_c__String__assignn(&pub.data, hello, sizeof(hello));

    RCSOFTCHECK(rcl_publish(&publisher, &pub, NULL));

    //初期化
    HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_RESET);
  /* Infinite loop */
  for(;;)
  {
	  // エグゼキューターを実行してリクエストを処理
	  rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));

	  osDelay(100);
  }
  // 終了処理
  	RCCHECK(rcl_service_fini(&service, &node));
  	RCCHECK(rcl_service_fini(&publisher, &node));
  	RCCHECK(rcl_service_fini(&subscriber, &node));
  	RCCHECK(rcl_node_fini(&node));
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

