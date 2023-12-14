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
#include "dma.h"
#include "tim.h"
#include "gpio.h"
// カスタムメッセージのインクルード
#include <custom_test_msgs/srv/add_three_ints.h>
#include <drive_msgs/msg/diff_drive.h>
#include <drive_msgs/msg/omni.h>

//canlibを使うためのinclude
#include "can.h"
#include "CAN_Main.h"
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

//CANモジュール基盤の設定
NUM_OF_DEVICES num_of_devices;

//mcmdの設定
MCMD_HandleTypedef mcmd4M1_struct;
MCMD_Feedback_Typedef mcmdM1_fb;//MCMDM1からのフィードバックを受け取る構造体を定義
MCMD_HandleTypedef mcmd4M2_struct;
MCMD_Feedback_Typedef mcmdM2_fb;//MCMDM2からのフィードバックを受け取る構造体を定義
MCMD_HandleTypedef mcmd4M3_struct;
MCMD_Feedback_Typedef mcmdM3_fb;//MCMDM1からのフィードバックを受け取る構造体を定義
MCMD_HandleTypedef mcmd4M4_struct;
MCMD_Feedback_Typedef mcmdM4_fb;//MCMDM2からのフィードバックを受け取る構造体を定義

//サーボの設定
CANServo_Param_Typedef servo_param;
CAN_Device servo_device;

//エアシリの設定
CAN_Device air_device;
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
/* Definitions for SysCeckTask */
osThreadId_t SysCeckTaskHandle;
uint32_t SysCeckTaskBuffer[ 512 ];
osStaticThreadDef_t SysCeckTaskControlBlock;
const osThreadAttr_t SysCeckTask_attributes = {
  .name = "SysCeckTask",
  .cb_mem = &SysCeckTaskControlBlock,
  .cb_size = sizeof(SysCeckTaskControlBlock),
  .stack_mem = &SysCeckTaskBuffer[0],
  .stack_size = sizeof(SysCeckTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
//このコード固有の変数
bool finishCANsetting = false;
float cmd_motor[4] = {0,0,0,0};

bool cubemx_transport_open(struct uxrCustomTransport * transport);
bool cubemx_transport_close(struct uxrCustomTransport * transport);
size_t cubemx_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err);
size_t cubemx_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);
void * microros_allocate(size_t size, void * state);
void microros_deallocate(void * pointer, void * state);
void * microros_reallocate(void * pointer, size_t size, void * state);
void * microros_zero_allocate(size_t number_of_elements, size_t size_of_element, void * state);

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan){
    WhenTxMailbox0_1_2CompleteCallbackCalled();
}

void HAL_CAN_TxMailbox0AbortCallback(CAN_HandleTypeDef *hcan){
    WhenTxMailbox0_1_2AbortCallbackCalled();
}

void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan){
    WhenTxMailbox0_1_2CompleteCallbackCalled();
}

void HAL_CAN_TxMailbox1AbortCallback(CAN_HandleTypeDef *hcan){
    WhenTxMailbox0_1_2AbortCallbackCalled();
}

void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan){
    WhenTxMailbox0_1_2CompleteCallbackCalled();
}

void HAL_CAN_TxMailbox2AbortCallback(CAN_HandleTypeDef *hcan){
    WhenTxMailbox0_1_2AbortCallbackCalled();
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
    WhenCANRxFifo0MsgPending(hcan, &num_of_devices);
}
//can通信の設定
void canSetting(){
	printf("Start Initializing CAN System:Begin\n\r");
	HAL_Delay(10);

	CAN_SystemInit(&hcan1); // F7のCAN通信のinit

	// デバイス数の設定
	num_of_devices.mcmd3 = 2;
	num_of_devices.mcmd4 = 0;
	num_of_devices.air = 0;
	num_of_devices.servo = 0;

	printf("Start Initializing CAN System:End\n\r");
	HAL_Delay(10);
	CAN_WaitConnect(&num_of_devices);  // 設定された全てのCANモジュール基板との接続が確認できるまで待機
}

//モータ1のmcmd設定
void mcmdMoter1Setting(){
	    // 接続先のMCMDの設定
	    mcmd4M1_struct.device.node_type = NODE_MCMD3;  // nodeのタイプ
	    mcmd4M1_struct.device.node_id =0;  // 基板の番号 (基板上の半固定抵抗を回す事で設定できる)
	    mcmd4M1_struct.device.device_num = 0;  // モーターの番号(0→M1,1→M2)

	    // 制御パラメータの設定
	    mcmd4M1_struct.ctrl_param.ctrl_type = MCMD_CTRL_DUTY;  //制御タイプを設定
	    mcmd4M1_struct.ctrl_param.PID_param.kp = 0.3f;  // Pゲイン 1.0
	    mcmd4M1_struct.ctrl_param.PID_param.ki = 0.0f;  // Iゲイン 0.0
	    mcmd4M1_struct.ctrl_param.PID_param.kd = 0.0f;  // Dゲイン 0.0 (Dゲインは使いにくい)
	    mcmd4M1_struct.ctrl_param.accel_limit = ACCEL_LIMIT_ENABLE;  // PIDの偏差をclipするか
	    mcmd4M1_struct.ctrl_param.accel_limit_size = 2.0f;  // PIDの偏差をclipする場合の絶対値のmax値
	    mcmd4M1_struct.ctrl_param.feedback = MCMD_FB_ENABLE;  // MCMDからF7にフィードバックを送信するか否か
	    mcmd4M1_struct.ctrl_param.timup_monitor = TIMUP_MONITOR_DISABLE;  // timeupは未実装なのでDISABLE。
	    mcmd4M1_struct.enc_dir = MCMD_DIR_FW;  // Encoderの回転方向設定
	    mcmd4M1_struct.rot_dir = MCMD_DIR_BC;  // モーターの回転方向設定
	    mcmd4M1_struct.quant_per_unit = 59.0/6400.0f;  // エンコーダーの分解能に対する制御値の変化量の割合

	    // 原点サーチの設定
	    mcmd4M1_struct.limit_sw_type = LIMIT_SW_NO;  // 原点サーチにNomaly Closedのスイッチを用いる
	    mcmd4M1_struct.calib = CALIBRATION_DISABLE;  // 原点サーチを行うかどうか。
	    mcmd4M1_struct.calib_duty = -0.2f;  // 原点サーチ時のduty
	    mcmd4M1_struct.offset = 0.0f;  // 原点のオフセット
	    mcmd4M1_struct.fb_type = MCMD_FB_POS;  // 読み取った位置情報をF7にフィードバックする。

	    // パラメータなどの設定と動作命令をMCMDに送信する
		 MCMD_init(&mcmd4M1_struct);
		 HAL_Delay(10);
		 MCMD_Calib(&mcmd4M1_struct);  // キャリブレーションを行う
		 HAL_Delay(5000);  // キャリブレーションが終わるまで待つ
		 MCMD_SetTarget(&mcmd4M1_struct, 0.00f);  // 目標値を設定
}

//モータ2のmcmd設定
void mcmdMoter2Setting(){
	    // 接続先のMCMDの設定
	    mcmd4M2_struct.device.node_type = NODE_MCMD3;  // nodeのタイプ
	    mcmd4M2_struct.device.node_id = 0;  // 基板の番号 (基板上の半固定抵抗を回す事で設定できる)
	    mcmd4M2_struct.device.device_num = 1;  // モーターの番号(0→M1,1→M2)

	    // 制御パラメータの設定
	    mcmd4M2_struct.ctrl_param.ctrl_type = MCMD_CTRL_DUTY;  //制御タイプを設定
	    mcmd4M2_struct.ctrl_param.PID_param.kp = 0.3f;  // Pゲイン 1.0
	    mcmd4M2_struct.ctrl_param.PID_param.ki = 0.0f;  // Iゲイン 0.0
	    mcmd4M2_struct.ctrl_param.PID_param.kd = 0.0f;  // Dゲイン 0.0 (Dゲインは使いにくい)
	    mcmd4M2_struct.ctrl_param.accel_limit = ACCEL_LIMIT_ENABLE;  // PIDの偏差をclipするか
	    mcmd4M2_struct.ctrl_param.accel_limit_size = 2.0f;  // PIDの偏差をclipする場合の絶対値のmax値
	    mcmd4M2_struct.ctrl_param.feedback = MCMD_FB_ENABLE;  // MCMDからF7にフィードバックを送信するか否か
	    mcmd4M2_struct.ctrl_param.timup_monitor = TIMUP_MONITOR_DISABLE;  // timeupは未実装なのでDISABLE。
	    mcmd4M2_struct.enc_dir = MCMD_DIR_FW;  // Encoderの回転方向設定
	    mcmd4M2_struct.rot_dir = MCMD_DIR_BC;  // モーターの回転方向設定
	    mcmd4M2_struct.quant_per_unit = 59.0/6400.0f;  // エンコーダーの分解能に対する制御値の変化量の割合

	    // 原点サーチの設定
	    mcmd4M2_struct.limit_sw_type = LIMIT_SW_NO;  // 原点サーチにNomaly Closedのスイッチを用いる
	    mcmd4M2_struct.calib = CALIBRATION_DISABLE;  // 原点サーチを行うかどうか。
	    mcmd4M2_struct.calib_duty = -0.2f;  // 原点サーチ時のduty
	    mcmd4M2_struct.offset = 0.0f;  // 原点のオフセット
	    mcmd4M2_struct.fb_type = MCMD_FB_POS;  // 読み取った位置情報をF7にフィードバックする。

	    // パラメータなどの設定と動作命令をMCMDに送信する
		 MCMD_init(&mcmd4M2_struct);
		 HAL_Delay(10);
		 MCMD_Calib(&mcmd4M2_struct);  // キャリブレーションを行う
		 HAL_Delay(5000);  // キャリブレーションが終わるまで待つ
		 MCMD_SetTarget(&mcmd4M2_struct, 0.00f);  // 目標値を設定
}

void mcmdMoter3Setting(){
	    // 接続先のMCMDの設定
	    mcmd4M3_struct.device.node_type = NODE_MCMD3;  // nodeのタイプ
	    mcmd4M3_struct.device.node_id = 5;  // 基板の番号 (基板上の半固定抵抗を回す事で設定できる)
	    mcmd4M3_struct.device.device_num = 1;  // モーターの番号(0→M1,1→M2)

	    // 制御パラメータの設定
	    mcmd4M3_struct.ctrl_param.ctrl_type = MCMD_CTRL_DUTY;  //制御タイプを設定
	    mcmd4M3_struct.ctrl_param.PID_param.kp = 0.3f;  // Pゲイン 1.0
	    mcmd4M3_struct.ctrl_param.PID_param.ki = 0.0f;  // Iゲイン 0.0
	    mcmd4M3_struct.ctrl_param.PID_param.kd = 0.0f;  // Dゲイン 0.0 (Dゲインは使いにくい)
	    mcmd4M3_struct.ctrl_param.accel_limit = ACCEL_LIMIT_ENABLE;  // PIDの偏差をclipするか
	    mcmd4M3_struct.ctrl_param.accel_limit_size = 2.0f;  // PIDの偏差をclipする場合の絶対値のmax値
	    mcmd4M3_struct.ctrl_param.feedback = MCMD_FB_ENABLE;  // MCMDからF7にフィードバックを送信するか否か
	    mcmd4M3_struct.ctrl_param.timup_monitor = TIMUP_MONITOR_DISABLE;  // timeupは未実装なのでDISABLE。
	    mcmd4M3_struct.enc_dir = MCMD_DIR_FW;  // Encoderの回転方向設定
	    mcmd4M3_struct.rot_dir = MCMD_DIR_BC;  // モーターの回転方向設定
	    mcmd4M3_struct.quant_per_unit = 59.0/6400.0f;  // エンコーダーの分解能に対する制御値の変化量の割合

	    // 原点サーチの設定
	    mcmd4M3_struct.limit_sw_type = LIMIT_SW_NO;  // 原点サーチにNomaly Closedのスイッチを用いる
	    mcmd4M3_struct.calib = CALIBRATION_DISABLE;  // 原点サーチを行うかどうか。
	    mcmd4M3_struct.calib_duty = -0.2f;  // 原点サーチ時のduty
	    mcmd4M3_struct.offset = 0.0f;  // 原点のオフセット
	    mcmd4M3_struct.fb_type = MCMD_FB_POS;  // 読み取った位置情報をF7にフィードバックする。

	    // パラメータなどの設定と動作命令をMCMDに送信する
		 MCMD_init(&mcmd4M3_struct);
		 HAL_Delay(10);
		 MCMD_Calib(&mcmd4M3_struct);  // キャリブレーションを行う
		 HAL_Delay(5000);  // キャリブレーションが終わるまで待つ
		 MCMD_SetTarget(&mcmd4M3_struct, 0.00f);  // 目標値を設定
}

void mcmdMoter4Setting(){
	    // 接続先のMCMDの設定
	    mcmd4M4_struct.device.node_type = NODE_MCMD3;  // nodeのタイプ
	    mcmd4M4_struct.device.node_id =5;  // 基板の番号 (基板上の半固定抵抗を回す事で設定できる)
	    mcmd4M4_struct.device.device_num = 0;  // モーターの番号(0→M1,1→M2)

	    // 制御パラメータの設定
	    mcmd4M4_struct.ctrl_param.ctrl_type = MCMD_CTRL_DUTY;  //制御タイプを設定
	    mcmd4M4_struct.ctrl_param.PID_param.kp = 0.3f;  // Pゲイン 1.0
	    mcmd4M4_struct.ctrl_param.PID_param.ki = 0.0f;  // Iゲイン 0.0
	    mcmd4M4_struct.ctrl_param.PID_param.kd = 0.0f;  // Dゲイン 0.0 (Dゲインは使いにくい)
	    mcmd4M4_struct.ctrl_param.accel_limit = ACCEL_LIMIT_ENABLE;  // PIDの偏差をclipするか
	    mcmd4M4_struct.ctrl_param.accel_limit_size = 2.0f;  // PIDの偏差をclipする場合の絶対値のmax値
	    mcmd4M4_struct.ctrl_param.feedback = MCMD_FB_ENABLE;  // MCMDからF7にフィードバックを送信するか否か
	    mcmd4M4_struct.ctrl_param.timup_monitor = TIMUP_MONITOR_DISABLE;  // timeupは未実装なのでDISABLE。
	    mcmd4M4_struct.enc_dir = MCMD_DIR_FW;  // Encoderの回転方向設定
	    mcmd4M4_struct.rot_dir = MCMD_DIR_BC;  // モーターの回転方向設定
	    mcmd4M4_struct.quant_per_unit = 59.0/6400.0f;  // エンコーダーの分解能に対する制御値の変化量の割合

	    // 原点サーチの設定
	    mcmd4M4_struct.limit_sw_type = LIMIT_SW_NO;  // 原点サーチにNomaly Closedのスイッチを用いる
	    mcmd4M4_struct.calib = CALIBRATION_DISABLE;  // 原点サーチを行うかどうか。
	    mcmd4M4_struct.calib_duty = -0.2f;  // 原点サーチ時のduty
	    mcmd4M4_struct.offset = 0.0f;  // 原点のオフセット
	    mcmd4M4_struct.fb_type = MCMD_FB_POS;  // 読み取った位置情報をF7にフィードバックする。

	    // パラメータなどの設定と動作命令をMCMDに送信する
		 MCMD_init(&mcmd4M4_struct);
		 HAL_Delay(10);
		 MCMD_Calib(&mcmd4M4_struct);  // キャリブレーションを行う
		 HAL_Delay(5000);  // キャリブレーションが終わるまで待つ
		 MCMD_SetTarget(&mcmd4M4_struct, 0.00f);  // 目標値を設定
}


//サーボ基盤設定
void servoSetting(){
	// Servo基板のdevice設定
	servo_device.node_type = NODE_SERVO;
	servo_device.node_id = 0;
	servo_device.device_num = 0;//0~3を指定する

	// Servo基板のパラメータ (offset以外はあまり変更しない)
	servo_param.angle_range=270.0f;//サーボの動作範囲
	servo_param.angle_offset=0.0f;//原点の位置
	servo_param.pulse_width_max=2.4f;//サーボの制御のPWM信号のパルス幅の最大値
	servo_param.pulse_width_min=0.5f;//サーボの制御のPWM信号のパルス幅の最小値
	servo_param.pwm_frequency=50;//PWM周波数（この変更は未実装
}

//エアシリ基盤設定
void airSetting(){
	air_device.node_type = NODE_AIR; //エアシリンダ基盤であることを示す
	air_device.node_id = 0; //基板の番号

	//初期化
	 for(uint8_t i=PORT_1; i<=PORT_8; i++){  //すべてのポートを初期化しないとAir基板は動かない
		air_device.device_num = i; // (i番ポートを指定)
		AirCylinder_Init(&air_device, AIR_OFF);
		HAL_Delay(10);  // このdelayは必要
	 }
}
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartSysCheckTask(void *argument);

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

  /* creation of SysCeckTask */
  SysCeckTaskHandle = osThreadNew(StartSysCheckTask, NULL, &SysCeckTask_attributes);

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
//duty制限
double limit = 250.0;
double duty_limmiter(double input){
	if(input > limit){
		input = limit;
	}
	return input;
}
//駆動用関数
void run_motor(double m1,double m2){

	//初期化
	HAL_GPIO_WritePin(GPIOB, M11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, M12_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, M21_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, M22_Pin, GPIO_PIN_RESET);

	//制御値を設定
	if(m1 > 0){
		HAL_GPIO_WritePin(GPIOB, M11_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, M12_Pin, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty_limmiter(m1*100.0));
	}else if(m1 < 0){
		HAL_GPIO_WritePin(GPIOB, M11_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, M12_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty_limmiter(m1*100.0*-1.0));
	}

	if(m2 > 0){
		HAL_GPIO_WritePin(GPIOB, M21_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, M22_Pin, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, duty_limmiter(m2*100.0));
	}else if(m2 < 0){
		HAL_GPIO_WritePin(GPIOB, M21_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, M22_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, duty_limmiter(m2*100.0*-1.0));
	}

}
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
	  const drive_msgs__msg__Omni * sub = (const drive_msgs__msg__Omni *)msgin;

	  char hearing[] = "I'm hearing from f7";
	  rosidl_runtime_c__String__assignn(&pub.data, hearing, sizeof(hearing));

	  //データのpublish
	  RCSOFTCHECK(rcl_publish(&publisher, &pub, NULL));

	  cmd_motor[0] = sub->mfontright;
	  cmd_motor[1] = sub->mfrontleft;
	  cmd_motor[2] = sub->mbackright;
	  cmd_motor[3] = sub->mbackleft;

	  printf("%f:%f:%f:%f",cmd_motor[0],cmd_motor[1],cmd_motor[2],cmd_motor[3]);
}
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  //MX_USB_DEVICE_Init();
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
		  ROSIDL_GET_MSG_TYPE_SUPPORT(drive_msgs, msg, Omni),
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
    char hello[] = "initialized from f7";
    rosidl_runtime_c__String__assignn(&pub.data, hello, sizeof(hello));

    RCSOFTCHECK(rcl_publish(&publisher, &pub, NULL));

    //初期化
    HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_RESET);

	//記事ではmcmdなどの初期化コードを描くことになっている場所
	canSetting();
	//servoSetting();
	mcmdMoter1Setting();
	mcmdMoter2Setting();
	mcmdMoter3Setting();
	mcmdMoter4Setting();
	//airSetting();
	printf("calibrationFinished\r\n");

	finishCANsetting = true;

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

/* USER CODE BEGIN Header_StartSysCheckTask */
/**
* @brief Function implementing the SysCeckTask thread.
* @param argument: Not used
* @retval None
*/
bool finishCheck = false;
//freeRTOSの動作確認用
void freeRTOSChecker(){//無限ループの中で実行
	HAL_GPIO_TogglePin(GPIOB, LD2_Pin);  // PINのPin stateを反転
	printf("RTOSchecking\r\n");

}

//M1の動作確認用
void mcmdMoter1Checker(){
		 MCMD_SetTarget(&mcmd4M1_struct, 0.05f);  // 目標値を設定
		 MCMD_Control_Enable(&mcmd4M1_struct);  // 制御開始
		 printf("MCMDM1controllStart\r\n");
		 osDelay(1000);
		 MCMD_SetTarget(&mcmd4M1_struct, 0.00f);  // 目標値を設定
	}

//M2の動作確認用
void mcmdMoter2Checker(){
		 MCMD_SetTarget(&mcmd4M2_struct, 0.05f);  // 目標値を設定
		 MCMD_Control_Enable(&mcmd4M2_struct);  // 制御開始
		 printf("MCMDM2controllStart\r\n");
		 osDelay(1000);
		 MCMD_SetTarget(&mcmd4M2_struct, 0.00f);  // 目標値を設定
	}

//M1の動作確認用
void mcmdMoter3Checker(){
		 MCMD_SetTarget(&mcmd4M3_struct, 0.05f);  // 目標値を設定
		 MCMD_Control_Enable(&mcmd4M3_struct);  // 制御開始
		 printf("MCMDM3controllStart\r\n");
		 osDelay(1000);
		 MCMD_SetTarget(&mcmd4M3_struct, 0.00f);  // 目標値を設定
	}

//M2の動作確認用
void mcmdMoter4Checker(){
		 MCMD_SetTarget(&mcmd4M4_struct, 0.05f);  // 目標値を設定
		 MCMD_Control_Enable(&mcmd4M4_struct);  // 制御開始
		 printf("MCMDM4controllStart\r\n");
		 osDelay(1000);
		 MCMD_SetTarget(&mcmd4M4_struct, 0.00f);  // 目標値を設定
	}

//M1のエンコーダー確認用
void mcmdEncorder1Checker(){//無限ループの中で実行
	mcmdM1_fb = Get_MCMD_Feedback(&(mcmd4M1_struct.device));
	printf("value of M1 %d\r\n",(int)(mcmdM1_fb.value));
}

//M2のエンコーダー確認用
void mcmdEncorder2Checker(){//無限ループの中で実行
	mcmdM2_fb = Get_MCMD_Feedback(&(mcmd4M2_struct.device));
	printf("value of M2 %d\r\n",(int)(mcmdM2_fb.value));
}

//サーボの動作確認用
void servoChecker(){
	ServoDriver_Init(&servo_device, &servo_param);  // Servo基板にパラメータを送信
	osDelay(100);  // 適切なdelayを入れる
	ServoDriver_SendValue(&servo_device, 20.0f);  // サーボが20.0度になるように回転させる
}

//エアシリの動作確認用
void airChecker(){
	for(uint8_t i=PORT_1; i<=PORT_8; i++){  //すべてのポートを初期化しないとAir基板は動かない
	    air_device.device_num = i; // (i番ポートを指定)
	    AirCylinder_Init(&air_device, AIR_OFF);
	    osDelay(10);  // このdelayは必要
	  }
	  air_device.device_num=0; // とりあえず0番ポートのエアシリンダを動かします。
	  AirCylinder_SendOutput(&air_device, AIR_ON);  // 0番ポートの電磁弁がonになる
	  osDelay(1000);
	  AirCylinder_SendOutput(&air_device, AIR_OFF); // 0番ポートの電磁弁がoffになる
	  osDelay(1000);
}
/* USER CODE END Header_StartSysCheckTask */
void StartSysCheckTask(void *argument)
{
  /* USER CODE BEGIN StartSysCheckTask */
  /* Infinite loop */
  for(;;)
  {
	  if(finishCANsetting){
		  if(!finishCheck){
		  		mcmdMoter1Checker();
		  		mcmdMoter2Checker();
		  		mcmdMoter3Checker();
		  		mcmdMoter4Checker();
		  		osDelay(2000);
		  		//servoChecker();
		  		//airChecker();
		  		finishCheck = true;
		  	  }
	  }
	  freeRTOSChecker();
	  //mcmdEncorder1Checker();
	  //mcmdEncorder2Checker();
	  osDelay(1000);
  }
  /* USER CODE END StartSysCheckTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

