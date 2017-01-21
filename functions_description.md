************************************************************
以下関数シリーズの説明

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
