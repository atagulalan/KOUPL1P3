Labirent Oyunu
Bu readme.txt dosyası, Labirent Oyunu koduna aittir.
Bu paket, kod ile aynı dizin içerisinde bulunacaktır.


1-PAKETİN İÇERİĞİ:
----------
160202034-160202015.c - Labirent Oyunu'nun kaynak kodu.
readme.txt - Bu dosya.
Labirent.exe - Kaynak kodunun Windows Platformu için derlenmiş hali.
----------

2-SİSTEM GEREKSİNİMLERİ:
-------------------
gcc - GNU Compiler Colection - http://gcc.gnu.org/
-------------------

3-KURULUM:
-------------------
Paket içeriğini yukarıda görebilirsiniz.

Bu kod, iki adet Windows kurulu makinede çalıştırıldı:
- Ata'nın Windows 10 yüklü masaüstü bilgisayarında.
- Oğuzhan'ın Windows 8.1 yüklü dizüstü bilgisayarında.

Bu iki durumda da kod, herhangi bir hata vermeden, daha önceden belirlenen kriterlere
uygun çalıştı.

Windows harici bir makinede çalıştırmak istiyorsanız, kaynak kodu Windows
bağımlılıklarından ayırıp derlemeniz gerekiyor.

YUM komutunu kullanarak bu programın çalışması için gereken paketleri indirebilirsiniz.
Bazı derlemelerde Grafik Arayüzü ile de arama yapabilir ve paketi indirebilirsiniz.

Ubuntuda da aynı şekilde, APP-GET komutunu kullanabilir, veya Synaptic Paket Yöneticisi
ile paketlerde arama yapıp belirtilen paketi indirebilirsiniz.
-------------------


4-KODU DERLEMEK:
------------------
Artık bilgisayarımızda kurulu olan GCC ile kodu kolayca derleyebiliriz.

Windows için:

>gcc 160202034-160202015.c –o Labirent.exe

Linux / Unix için:

>gcc 160202034-160202015.c -o Labirent


Derleme bittikten sonra kolayca programı çalıştırabilirsiniz.
------------------


5- PARAMETRELER
---------------------------
Kodun çalışması için başlangıçta herhangi bir parametre gerekmiyor.
------------------



6- PROGRAMIN KULLANIMI
-----------------------------
Program, öncelikle sizden labirentin boyutunu isteyecektir. Verdiğiniz cevabın, istenen
formata ve konsol boyutuna uygun olması gerekmektedir. Bu cevap labirenti oluşturacak, 
size oluşturulan labirenti gösterecektir.

Labirent oluşturulduktan sonra sizden başlangıç ve bitiş noktaları istenecektir.

Girdiğiniz ilk değer giriş noktasını labirentte işaretleyecek ve size gösterecektir.
Girdiğiniz ikinci değer çıkış noktasını labirentte işaretleyecek ve size gösterecektir.

İstenen değerler formata uygun değil veya istenen sınırların dışında ise kullanıcıdan
tekrar istenecektir.

Verilen değerler kapsamında labirent çözümü başlayacak ve daha önceden belirlenmiş
ayarlara göre labirentin çözümü size gösterilecektir.

Labirent çözüldükten sonra çözümünün olup olmadığı ekrana yazdırılacak ve programdan
çıkılması için kullanıcıdan bir giriş beklenecektir.
-----------------------------


Program dilinin İngilizce olması hakkında: 
-----------------------------
Programın kaynak kodu içinde bazı ayarlar mevcuttur. Bu ayarlar değiştirilerek programın
dili İngilizce veya Türkçe yapılabilir. 
-----------------------------