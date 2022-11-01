# FreeRTOS                             
FreeRTOS bir mikrodenetleyici üzerinde çalışabilecek şekilde tasarlanmış bir işletim sistemidir. Gömülü 
sistemlerde FreeRTOS gibi farklı işletim sistemleri de bulunmaktadır. Bunlardan birkaçı VxWorks,QNX,Integrity dir. 
FreeRTOS bunların içinde lisanssız olanlarından. FreeRTOS ile aynı kod tabanını paylaşan lisanslı yazılımlar da 
bulunmaktadır(OpenRTOS,SafeRTOS). 

### FreeRTOS Özellikleri
- Pre-emptive(öncelik) veya co-operative(işbirliği) çalışması.
- Çok esnek task önceliği atanabilmesi.
- Esnek ve hızlı task notification(bildirim) mekanizması.
- Queues( Kuyruklar)
- Binary ve Counting Semaphore
- Mutex ve Recursive Mutex
- Yazılımsal Timer’lar
- Event grupları
- Tick hook ve ıdle hook fonksiyonu
- Stack overflow kontorolü
- Opsiyonel ticari lisans versiyonları


## Multitasking (Çoklu Görev)
FreeRTOS, gömülü uygulamaların hard real-time gereksinimlerini karşılamak için oluşturulmuş bir gerçek zamanlı 
kernel’dır. FreeRTOS birden fazla işin(task veya thread) organize olarak çalışmasını sağlar. Buna da multitasking 
denir. RTOS da task(veya thread) olarak isimlendirilen iş parçacıkları bulunmaktadır. İşlemci bu iş parçacıklarını 
belli zamanlarda belli bir önceliğe göre çalıştırır yani birden fazla işi aynı anda yapar(yapıyormuş gibi görünür).
Aslında tek çekirdekli işlemci üzerinde herhangi bir zamanda tek iş parçacığı çalıştırılır. RTOS da bu iş 
parçacıkları öncelik ve zamana bağlı olarak aynı anda çalışıyormuş gibi işlemci üzerinde çalışır. Zamana bağlı 
olduğundan dolayı gerçek zamanlı kavramı buradan gelir.

> Gerçek zamanlı sistemlerde hard real-time gereksinime sahip thread’ler soft real-time gereksinime sahip 
> thread’lere göre daha öncelikli olarak çalıştırılır.

> FreeRTOS da her bir iş parçacığı “task” olarak isimlendirilir fakat daha spesifik adı “thread”‘tir ve genellikle 
> thread daha çok kullanılır.


## Neden Real-Time Kernel Kullanırız?
- Kernel execution timing ten sorumludur ve uygulamaya zamanla ilgili bir API sağlar. Böylece uygulama kodunun daha basit ve boyutunun küçük olmasını sağlar.
- Modülerlik; Task’lar her biri iyi tanımlanmış birer modüldür.
- Task’lar aynı zamanda iyi tanımlanmış birer arayüzdür. Böylece geliştirmeyi takım ile yapmayı kolaylaştırır.
- Testleri kolaydır.
- Büyük modüler yapısı ve daha az bağımlı olmasının sonucu olarak fazla efor harcamadan kodlar tekrardan 
kullanılabilir.
- Verim; Bir kernel kullanmak yazılımın tamamen olay güdümlü(event-driven) olmasını sağlar. Bu yüzden
gerçekleşmemiş olaylar için yoklama(polling) ile zaman kaybedilmez. Task sadece gerekli olduğunda yürütülür.
- Güç yönetimi; İşlemci üzerinde en az bir task yürütülmelidir. Bu yüzden başlangıçta “Idle task” adında boş bir 
task oluşturulur. Eğer kullanıcının tanımladığı tasklerden hiçbiri işlemci üzerinde yürütülmez ise “Idle task” 
otomatik olarak yürütülür. Bu task içerisinde işlemci düşük güç moduna alınarak güç tasarrufu yapılabilir.

## CMSIS - RTOS             
CMSIS-RTOS cortex-M tabanlı işlemciler için geliştirilmiş bir ortak API’dir. Bu API arka planda üçüncü parti bir 
RTOS API kullanır. CubeMX ile STM32 üzerinde FreeRTOS kullanmak istersek araya bu CMSIS-RTOS katmanı girer. 
CMSIS-RTOS API’sinin geliştirilmesindeki amaç RTOS API leri arasında taşınabilen standartlaştırılmış ortak bir 
katman sağlamaktır.

## Heap Memory Yönetimi
Bu yazı dizisinde zamanla task ,queue,semaphore ve mutex gibi kernel objelerini tanıyacağız. Bu objeler her 
oluşturulduğunda RTOS kernel’ı RAM’e ihtiyaç duyar. FreeRTOS’u mümkün oluğunca daha kolay kullanmak için bu 
objeler derleme aşamasında hafızada oluşturulmaz. Dinamik olarak program çalıştırılırken oluşturulur. 
FreeRTOS’da her kernel objesi oluşturulurken RAM de bir alan ayrılır(allocate). Bu kernel objeleri silindiği 
zaman RAM de ayrılan alanlar temizlenir(free). Bu durum RAM kullanımını minimuma indirir.

Hafıza standard library fonksiyonlarından malloc() ve free() fonksiyonları kullanılarak allocate ve deallocate 
edilebilir fakat FreeRTOS malloc() fonksiyonunu doğrudan kullanmaz. malloc() fonksiyonu yerine pvPortMalloc() 
fonksiyonunu, free() fonksiyonu yerine ise vPortFree() fonksiyonunu kullanır. Bunlar public tanımlı 
fonksiyonlar oldukları için uygulama kodu içerisinden de çağrılabilir.



## Bellek Ayırma Düzenleri
Gömülü sistemlerde kernel objelerinin scheduler başlatılmadan önce tanımlanması yaygındır. Bu durumda bellek, 
sistem herhangi bir gerçek zamanlı işi çalıştırmaya başlamadan önce kernel tarafından dinamik olarak ayrılır. Bu 
seçilen bellek ayrıma düzeninin kod boyutu ve basitlik gibi özelliklerinin dikkate alınarak seçileceği anlamına 
gelir.


**Heap_1** : Heap_1.c  pvPortMalloc() fonksiyonunun çok basit bir versiyonunu kullanır ve vPortFree() fonksiyonunu 
kullanmaz. Uygulama tarafından bir task veya diğer kernel objeleri silinemez. Bu yüzden task gibi kernel 
objelerinin oluşturulduğu ve silinmediği uygulamalar için tercih edilebilir. pvPortMalloc() fonksiyonu her 
çağrıldığında heap_1 basit bir dizini küçük bloklara böler. Bu dizin FreeRTOS Heap olarak isimlendirilir ve 
dizinin boyutu FreeRTOSConfig.h dosyası içerisindeki configTOTAL_HEAP_SIZE makrosuna göre belirlenir.
Oluşturulan her task’ın bir  task kontrol bloğu (TCB) vardır ve heap te blok olarak ayrılır.



- A: Henüz hiçbir task oluşturulmadan önceki dizin.
- B: Bir task oluşturulduktan sonraki dizin
- C: Üç task oluşturulduktan sonraki dizin.


**Heap_2**:  Heap_2 eski olduğu için bunun yerine heap_4 daha çok tercih edilir. Geriye dönük uyumluluk için yine 
de FreeRTOS dağıtımlarında tutulur.
Heap_2 en iyi yerleştirme algoritmasını( best fitting)  kullanır ve heap_1 den farklı olarak önceden ayrılmış 
blokları temizler(free). Heap_2 oluşturulan task’lara ayrılan yığın boyutunun değişmediği ve task’ların tekrar 
tekrar oluşturulup silindiği uygulamalar için uygundur.



Yukarıdaki resimde görüldüğü gibi önceden oluşturulmuş üç task’ten biri silinmiş ve daha sonra başka bir task 
oluşturulmuş. Son oluşturulan task daha önceden silinen bir taskın RAM’ de kapladığı alanı kullanır. Burada 
silinen ve oluşturulan task boyutları aynıdır.

**Heap_3**:  Heap_3 standard library fonksiyonlarından malloc() ve free() yi kullanır.  Heap boyutu linker 
konfigurasyonu ile tanımlanır. Bu yüzden configTOTAL_HEAP_SIZE tanımlamasının bir etkisi yoktur. Deterministik 
değildir. RTOS kernel kod boyutunu önemli ölçüde arttırır.



**Heap_4**:  Bu şema ilk bulunan yere yerleştirme (first fitting) algoritmasını kullanır ve heap_2 nin aksine 
bitişik olan boş blokları tek bir blok haline getirir. Heap boyutu yine configTOTAL_HEAP_SIZE makrosu ile 
belirlenir.  Sürekli olarak task,queue,semaphore vb gibi RTOS objelerinin oluşturulup silindiği uygulamalar için 
uygundur.



Yukarıdaki resimde heap_4 ün RAM’i nasıl ayırdığı görülebilir. Burada B de bir task silindiğinde stack ve TCB için 
ayrılan alanlar tekrardan tek bir blok haline getirilir.  C de görüldüğü üzere bir başka RTOS objesi olan Queue 
oluşturulduğunda RAM da ilk bulunan uygun blok ayrılır. D de ise kullanıcının pvPortMalloc() fonksiyonunu 
çağırarak ayırdığı blok görülmektedir. Burada kullanıcın ayırmak istediği yığın boyutu RAM de ilk bulunan boşluğun 
boyutundan küçüktür.  E de ise Queue silindiği için otomatik olarak boşaltılan RAM görülmektedir. F de ise 
kullanıcının ayırdığı bellekte temizlendiği için üç bloğun hepsi tek bir boş blok haline getirilmiş.
Heap_4 deterministik değildir fakat çoğu C standard library implementasyonu olan malloc() ve free() fonksiyonundan 
daha verimlidir.


**Heap_5**:  Bellek ayırma ve temizleme için kullanılan algoritma Heap_4 ile aynıdır. Heap_4 ün aksine boyutu belli  bir diziden bellek ayırmakla sınırlı değildir. Heap_5 sistem tarafından sağlanan RAM in tek bir bitişik 
blok olarak görünmediği durumlarda kullanışlıdır. Heap_5 pvPortMalloc() fonksiyonu çağırılmadan önce başlatılması 
gereken tek bellek ayırma şemasıdır.  Heap_5 vPortDefineHeapRegions() fonksiyonu ile başlatılır.




















