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

                String plainText1 = "bbbbbbbb";
                String plainText2 = "bbbbbbbc";
                String key1 = "11111111";
                String key2 = "00000000";

                SecretKeyFactory myKeyFactory = SecretKeyFactory.getInstance("DES");
                byte[] byteKey1 = key1.getBytes();
                byte[] byteKey2 = key2.getBytes();

                DESKeySpec material1 = new DESKeySpec(byteKey1);
                DESKeySpec material2 = new DESKeySpec(byteKey2);

                SecretKey desKey1 = myKeyFactory.generateSecret(material1);
                SecretKey desKey2 = myKeyFactory.generateSecret(material2);

                Cipher desCipher1 = Cipher.getInstance("DES/ECB/NoPadding");
                Cipher desCipher2 = Cipher.getInstance("DES/ECB/NoPadding");

                desCipher1.init(Cipher.ENCRYPT_MODE, desKey1);
                desCipher2.init(Cipher.ENCRYPT_MODE, desKey2);

                byte[] bytes_P1 = plainText1.getBytes();
                byte[] bytes_P2 = plainText2.getBytes();

                byte[] byteCipher1_1 = desCipher1.doFinal(bytes_P1);
                byte[] byteCipher1_2 = desCipher2.doFinal(bytes_P1);
                byte[] byteCipher2_1 = desCipher1.doFinal(bytes_P2);
                byte[] byteCipher2_2 = desCipher2.doFinal(bytes_P2);

                System.out.println(byteCipher1_1.length);
                System.out.println(byteCipher1_2.length);
                System.out.println(byteCipher2_1.length);
                System.out.println(byteCipher2_2.length);

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