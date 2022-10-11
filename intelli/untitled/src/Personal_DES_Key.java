import java.io.UnsupportedEncodingException;
import java.nio.charset.StandardCharsets;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.spec.InvalidKeySpecException;
import javax.crypto.SecretKey;
import javax. crypto. SecretKeyFactory;
import javax.crypto.spec.DESKeySpec;

public class Personal_DES_Key {
    public static void main(String[] args) throws NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException, InvalidKeySpecException {
        SecretKeyFactory MyKeyFactory = SecretKeyFactory.getInstance("DES");
        byte[] mybytes = "science".getBytes(StandardCharsets.UTF_8);

        DESKeySpec myMaterial = new DESKeySpec(mybytes);
        SecretKey myDESkey = MyKeyFactory.generateSecret(myMaterial);
    }
}