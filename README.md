# mbed_PBL  

情報ＰＢＬの課題に取り組む用のレポジトリです

# 取扱説明書  

Gグループの作品は

1. **温度計**  
2. **カウンター**  

の機能を備えております  

mbedを起動して7セグが下から上にウェーブしている間に  
モードセレクトを行います  

右スイッチを押せば**温度計**が、  
左スイッチを押せば**カウンター**が起動します。  

また、モード実行時に左右のスイッチを同時に長押しをすると  
モード切り替えが出来ます。  

mbedのLEDが目印です  
LEDが4つとも光った後にスイッチから手を離すとモードセレクトに戻ります  

************************************************************
## 7セグメントLEDの扱いに関する大まかな方針  

「数値」→「7セグメントLEDに出力」の流れをざっくり説明しときます  

1. 数値を桁ごとに分割(上から3桁)  
2. 「数字ごとに対応するa~gのON/OFFの並び」をそれぞれの位の数字に当てはめる  
3. a~gまでのON/OFFを桁ごとにAnalogOutに代入  

これで数値が表示されます  
関数たちの詳しい説明等はレポジトリ内の

[description_of_main.md](https://github.com/tanacchi/mbed_PBL/blob/master/description_of_main.md)

を参照してください
