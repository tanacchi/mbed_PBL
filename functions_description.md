# main.cppの説明

## インクルードファイル

>```C++
>#include "mbed.h"
>```

## オブジェクト形式マクロ

>```C++
>#define MBED_VOLTAGE 3.3
>
>#define ON 1
>#define OFF 0
>#define SEGMENT_NUM 7
>#define DIGITS_NUM 3
>#define NUM_PATTERN 10
>#define MBED_LED_NUM 4
>#define WAIT_NUM 5
>
>#define SEGMENT_A p10
>#define SEGMENT_B p11
>#define SEGMENT_C p12
>#define SEGMENT_D p13
>#define SEGMENT_E p14
>#define SEGMENT_F p15
>#define SEGMENT_G p16
>#define SEG_POINT p17
>
>#define SWITCH_R p18
>#define SWITCH_L p19
>
>#define TMP_SENSOR_PIN p20
>
>#define DIG_1_PIN p21
>#define DIG_2_PIN p22
>#define DIG_3_PIN p23
>```

## 7セグメントLEDに関するもの

### class sevseg_LEDのメンバ関数

### その他

## モード選択に関するもの

## 温度計に関するもの

## カウンターに関するもの

## エラーメッセージに関するもの
>
>* `err_message();`
>```C++
>void err_message(){
>  int error_array[3][7] = {
>    {ON,  OFF, OFF, ON,  ON, ON,  ON},
>    {OFF, OFF, OFF, OFF, ON, OFF, ON},
>    {OFF, OFF, OFF, OFF, ON, OFF, ON}
>  };
>  while (1){
>    for (int i = 0; i < WIDTH; i++){
>      digits_init();
>      digit[i] = 0;
>      output_digit(error_array[i]);
>      wait(powpow(10, 3));
>    }
>  }
>}
>```
