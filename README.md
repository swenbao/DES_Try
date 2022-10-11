## F74102145 吳出右 資安作業3

本次加密使用 Java DES 函式，秘文差異比例的計算是自己寫的 method
以下是 sourse code

```java
import javax.crypto.*;
import javax.crypto.spec.DESKeySpec;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.spec.InvalidKeySpecException;

public class DESCipher
{
        public static void main(String[] args) throws NoSuchAlgorithmException, IllegalBlockSizeException,
                BadPaddingException, NoSuchPaddingException, InvalidKeyException, InvalidKeySpecException{
                System.out.println();

                String plainText1 = "bbbbbbb";
                String plainText2 = "bbbbbbc";
                String key1 = "11111111";
                String key2 = "11111112";

                SecretKeyFactory myKeyFactory = SecretKeyFactory.getInstance("DES");
                byte[] byteKey1 = key1.getBytes();
                byte[] byteKey2 = key2.getBytes();

                DESKeySpec material1 = new DESKeySpec(byteKey1);
                DESKeySpec material2 = new DESKeySpec(byteKey2);

                SecretKey desKey1 = myKeyFactory.generateSecret(material1);
                SecretKey desKey2 = myKeyFactory.generateSecret(material2);

                Cipher desCipher1 = Cipher.getInstance("DES");
                Cipher desCipher2 = Cipher.getInstance("DES");

                desCipher1.init(Cipher.ENCRYPT_MODE, desKey1);
                desCipher2.init(Cipher.ENCRYPT_MODE, desKey2);

                byte[] bytes_P1 = plainText1.getBytes();
                byte[] bytes_P2 = plainText2.getBytes();

                byte[] byteCipher1_1 = desCipher1.doFinal(bytes_P1);
                byte[] byteCipher1_2 = desCipher2.doFinal(bytes_P1);
                byte[] byteCipher2_1 = desCipher1.doFinal(bytes_P2);
                byte[] byteCipher2_2 = desCipher2.doFinal(bytes_P2);

                System.out.print("plaintext \""+plainText1+"\", key \"" + key1 + "\" : ");
                StringBuffer bitsCipher1_1 = new StringBuffer();
                for(int i = 0; i < byteCipher1_1.length ; i++) {
                        String s1_1 = String.format("%8s", Integer.toBinaryString(byteCipher1_1[i] & 0xFF)).replace(' ', '0');
                        bitsCipher1_1.append(s1_1);
                        System.out.print(s1_1+" | ");
                }
                System.out.println();
                StringBuffer bitsCipher1_2 = new StringBuffer();
                System.out.print("plaintext \"" + plainText1 + "\", key \"" + key2 + "\" : ");
                for(int i = 0; i < byteCipher1_2.length ; i++) {
                        String s1_2 = String.format("%8s", Integer.toBinaryString(byteCipher1_2[i] & 0xFF)).replace(' ', '0');
                        bitsCipher1_2.append(s1_2);
                        System.out.print(s1_2+" | ");
                }
                System.out.println();
                StringBuffer bitsCipher2_1 = new StringBuffer();
                System.out.print("plaintext \"" + plainText2 + "\", key \"" + key1 + "\" : ");
                for(int i = 0; i < byteCipher2_1.length ; i++) {
                        String s2_1 = String.format("%8s", Integer.toBinaryString(byteCipher2_1[i] & 0xFF)).replace(' ', '0');
                        bitsCipher2_1.append(s2_1);
                        System.out.print(s2_1+" | ");
                }
                System.out.println();
                StringBuffer bitsCipher2_2 = new StringBuffer();
                System.out.print("plaintext \"" + plainText2 + "\", key \"" + key2 + "\" : ");
                for(int i = 0; i < byteCipher2_2.length ; i++) {
                        String s2_2 = String.format("%8s", Integer.toBinaryString(byteCipher2_2[i] & 0xFF)).replace(' ', '0');
                        System.out.print(s2_2+" | ");
                        bitsCipher2_2.append(s2_2);
                }
                System.out.println("\n");
                System.out.println("P1.K1 vs P1.K2 : "+ (100*compare(bitsCipher1_1.toString(), bitsCipher1_2.toString())) + "%");
                System.out.println("P1.K1 vs P2.K1 : "+ (100*compare(bitsCipher1_1.toString(), bitsCipher2_1.toString())) + "%");

        }
        public static double compare(String a, String b) {
                int difference = 0;
                for(int i = 0; i < a.length(); i++){
                        if(a.charAt(i) != b.charAt(i)){
                                difference++;
                        }
                }
                double ratio = difference/(double)a.length();
                return ratio;
        }

}
```
上面的 sourse code 有兩種明文與兩種金鑰，所以總共有 4 種組合。
此為其輸出：
![](https://i.imgur.com/DtCGqrl.png)


採用其中兩種當作範例。

### 例 1. 相同明文，不同金鑰（差 1 bit）
明文為 `bbbbbbb`，金鑰 1 為 `11111111`，金鑰 2 為`11111112`


- plaintext `bbbbbbb`, key `11111111` 密文為：
`00101111 11010101 01111111 11101010 01000100 11001011 01110110 11101110` 
- plaintext `bbbbbbb`, key `11111112` 密文為：
`10000100 10000111 10011111 00000110 00111010 01010001 00011001 01000110` 

#### 密文差異比例：54.6875%

>細心的你可能有注意兩個奇怪的點：
>1. 為什麼明文是 7 個字元，也就是 56 bits
>2. 金鑰 1 跟 2 因為進位其實相差了 2 bits
>'1' 為 `00110001` '2'為`00110010`
>
>最下面我會解釋 Java DES 函式的一些神奇性質


---

### 例 2. 不同明文（差 1 bit ），相同金鑰
明文 1 為 `bbbbbbb`，明文 2 為`bbbbbbc`，金鑰 1 為`11111111`


- plaintext `bbbbbbb`, key `11111111` 密文為：
`00101111 11010101 01111111 11101010 01000100 11001011 01110110 11101110` 
- plaintext `bbbbbbc`, key `11111111` 密文為：
`10100001 01001110 11111101 01110001 01010101 10010101 11000110 11101011` 

#### 密文差異比例：43.75%

>細心的你可能有注意一個奇怪的點：
>1. 為什麼明文是 7 個字元，也就是 56 bits
>
>最下面我會解釋 Java DES 函式的一些神奇性質

---

### 實驗出的一些 java DES 神奇性質
首先，先來解釋第一點：為什麼明文只有 56 bits
我們來試試看明文用 8 個字元，也就是 64 bits 的時後，會發生什麼事
![](https://i.imgur.com/m2bmt4i.png)

密文竟然會變成 128 bits❗️❗️(輸出太長了，最後面塞不下被切掉)

我有去找相關資料，嘗試想要搞懂這是怎麼一回事，我查完結論是他似乎跟 Java DES 的 pedding 有關，不過這部分我還不是非常清楚它的什麼操作細節，導致了這個現象的發生。

嘗試了許多不同的組合：
- 1~7個字元的明文 -> 64 bits 密文
- 8~15個字元 -> 128 bits 密文
- 16~23個字元 -> 192 bits 密文

8 個字元的明文（64 bits）會膨脹到 (128 bits)的密文，我認為 pedding 灌水太多了。所以為了盡量減少 pedding 對於密文差異比例的影響：我選擇 7 個字元的明文，而非 8 個字元的明文，

---

第二個部分：金鑰 1 跟 2 因為進位其實相差了 2 bits
‘1’ 為 `00110001` '2’為 `00110010`

其實在更仔細看一下，在 Java DES 中要指定金鑰的話，只能指定 64 bits（8個字元），可是金鑰應該要 56 bits（7個字元）啊？
實際上，他是跳掉了第一步驟（56 bits -> 64 bits）
而在下一步驟中，每一個字元（每個 byte）的最後一個 bit 又會被捨棄掉（64 bits -> 56 bits）
所以真正觀察 `00110001` `00110010`只相差了一個 bit 因為最後一個 bit 會被捨棄。
也因此造就了一個神奇的景象：金鑰輸入 "11111111" 跟 "00000000" 加密起來會一模一樣
![](https://i.imgur.com/uHlBhkL.png)
