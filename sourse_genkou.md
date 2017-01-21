# 原稿


①データ取得から出力するまでの大まかな流れ

温度計について
まずセンサーなどから数値データを取得する(23.5, 123など)

数値データを桁ごとに分割

それぞれの桁の数義に対応するa~gの0or1を参照



　　　　　   　2　　  {ON,  ON,  OFF, ON,  ON,  OFF, ON }
      23.5 →  3  →  {ON,  ON,  ON,  ON,  OFF, OFF, ON }
               5      {ON,  OFF, ON,  ON,  OFF, ON , ON }


②Gitというバージョン管理システムを利用しました
    https://github.com/tanacchi/mbed_PBL
上記のサイトでソースコードの詳しい説明が見られます

