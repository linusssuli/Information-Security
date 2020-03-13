import java.util.Scanner;
import java.io.FileInputStream;
import java.io.IOException;
import java.security.PublicKey;
import java.security.cert.X509Certificate;
import java.security.cert.Certificate;
import java.security.cert.CertificateFactory;
import java.security.cert.CertificateException;

public class X509 {
    public static void main(String args[]) throws IOException {
        while(true)
        {
            Scanner choose = new Scanner(System.in);
            System.out.println("\n\n是否开始解析证书：Y(开始解析)/N(退出程序)");
            String peng = choose.nextLine();
            char ch = peng.charAt(0);
            
            switch(ch){
                case 'Y' :    
                    Scanner input = new Scanner(System.in);
                    System.out.println("\n请输入你想解析的证书地址：");
                    String str = input.next();
                    try
                    {

                        FileInputStream fs = new FileInputStream(str);
                        CertificateFactory cf = CertificateFactory.getInstance("X.509");
                        Certificate cer = cf.generateCertificate(fs);
                        X509Certificate pai = (X509Certificate)cer ;
                        // 检查合法性
                        pai.checkValidity();
                        // 获得版本
                        System.out.println("版本:           " + pai.getVersion());
                        // 获得序列号
                        System.out.println("序列号:         " + pai.getSerialNumber());
                        //签名使用算法
                        System.out.println("签名使用算法:   "+ pai.getSigAlgName());
                        //证书颁发者的值获取
                        System.out.println("颁发者:         " + pai.getIssuerDN().toString());
                        System.out.println("颁发者唯一标识: " + pai.getIssuerUniqueID());
                        //获取证书有效期
                        System.out.println("证书有效期从:   "+ pai.getNotBefore());
                        System.out.println("到:             "+ pai.getNotAfter());
                        //证书使用者的值获取
                        System.out.println("使用者：        " + pai.getSubjectDN());
                        System.out.println("使用者唯一标识：" + pai.getSubjectUniqueID());
                        //主题的签名
                        System.out.println("签名:           "+ pai.getSignature().toString());
                        // 从此证书中获得公钥
                        byte [] encode = pai.getPublicKey().getEncoded();
                        System.out.println("公钥:         ");
                        String key = "[";
                        for(int i = 0 ; i < encode.length ; i++)
                        {
                            int index = encode[i] & 0xff;
                            key += Integer.toString(index);
                            if(i < encode.length - 1) key += ", ";
                            if(i % 40 == 0 && i != 0){
                                key += "\n";
                            }
                        }
                        System.out.println(key + "]\n");
                    }
                    catch (CertificateException e) {
                        e.printStackTrace();
                    }
                    break;
                case 'N' :
                    System.exit(0);
                    break;
            }
        }
    }
};
