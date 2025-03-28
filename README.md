# MPI vs. OpenMP Performans Karşılaştırması

Paralel programlama, büyük ölçekli hesaplamaların ve veri işlemenin verimli bir şekilde gerçekleştirilmesini sağlar. Bu bağlamda, Message Passing Interface (MPI) ve Open Multi-Processing (OpenMP) gibi iki temel paralel programlama modeli kullanılır. MPI, dağıtık sistemlerdeki birden fazla işlemci arasında iletişim sağlarken, OpenMP ise paylaşılan bellekli sistemlerde iş parçacıklarını etkinleştirerek paralel hesaplama yapar.

---

## MPI (Message Passing Interface)

MPI, dağıtık sistemler ve küme bilgisayarlarında iletişim kurarak paralel programlamayı sağlayan bir kütüphane sistemidir. MPI kullanılarak, bağımsız işlemciler (nodelar) birbirleriyle veri paylaşır ve senkronize edilir.

### MPI'nin Avantajları:
- Dağıtık sistemlerde çok sayıda işlemciyle çalışabilir.
- Paylaşılan bellek sınırlamaları yoktur, böylece büyük ölçekli hesaplamalar desteklenir.
- Heterojen sistemlerde etkin çalışabilir.

### MPI'nin Dezavantajları:
- İşlemciler arasındaki mesajlaşma nedeniyle iletişim maliyeti yüksektir.
- Karmaşık senkronizasyon gerektirir.

---

## OpenMP (Open Multi-Processing)

OpenMP, paylaşılan bellekli çok çekirdekli sistemlerde iş parçacıkları kullanarak paralel hesaplamalar yapmaya olanak tanır.

### OpenMP'nin Avantajları:
- Kolay kullanılabilir, C ve Fortran kodlarına pragmalarla entegre edilebilir.
- Paylaşılan bellek kullanıldığı için işlemciler arası mesajlaşma ihtiyacı yoktur.
- Aynı program içinde hem seri hem de paralel işlemler uygulanabilir.

### OpenMP'nin Dezavantajları:
- Sadece paylaşılan bellekli sistemlerde çalışabilir, büyük ölçekli kümelerde etkisizdir.
- Bellek bant genişliği sınırları nedeniyle verimlilik düşebilir.

---

## Uygulama İşleyişi

Bu uygulamada, MPI ve OpenMP birlikte kullanılarak 10 milyon elemanlı bir dizi işlenmektedir. Program şu adımlardan oluşmaktadır:

1. **Veri Hazırlama**: Ana süreç (MASTER) tarafından rastgele sayılarla doldurulmuş bir dizi oluşturulur.
2. **Veri Paylaşımı**: MPI kullanarak dizi parçalara ayrılır ve her süreç (node) kendi parçasını alır.
3. **Paralel İşleme**:
   - OpenMP ile her MPI sürecindeki dizinin bir alt kümesi işlenir.
   - Paralel olarak her eleman için karekök ve logaritma hesaplanır.
4. **Sonuçların Birleştirilmesi**: MPI Reduce fonksiyonuyla tüm süreçlerin hesapladığı değerler toplanarak ana sürece gönderilir.
5. **Sonuçların Gösterimi**: Ana süreç (MASTER) tarafından hesaplanan son değerler ekrana yazdırılır.

---

## Performans Analizi

Bu sistemde 4 MPI süreci ve her süreçte 4 OpenMP iş parçacığı kullanılmıştır. Performans analizi aşağıdaki gibi özetlenebilir:

- **İletişim Gecikmesi:** MPI süreçleri arasında veri paylaşımı gerektiği için iletişim maliyeti oluşur.
- **Hesaplama Verimliliği:** OpenMP'nin iş parçacıkları sayesinde her MPI süreci içinde hesaplama süresi azaltılır.
- **Toplam Süre:** İşlemin toplam süresi 1 saniyenin altına düşerek yüksek verim elde edilmiştir.

---

## Sonuç

Bu uygulamada hem MPI hem de OpenMP kullanılarak hibrit bir paralel programlama modeli uygulanmıştır. Elde edilen sonuçlara göre:

- **OpenMP**, paylaşılan bellekli sistemlerde küçük ölçekli paralel hesaplamalar için uygundur.
- **MPI**, büyük ölçekli dağıtık sistemlerde iletişim maliyetine rağmen etkili bir çözümdür.
- **Hibrit Model**, her iki yöntemin avantajlarını birleştirerek daha iyi performans sağlayabilir.

Bu çalışmada, MPI ve OpenMP'nin birlikte kullanılmasıyla hesaplama süresi optimize edilmiş ve ölçeklenebilirlik artırılmıştır. Gelecekte farklı veri setleri ve donanım konfigürasyonları ile daha detaylı analizler yapılabilir.

