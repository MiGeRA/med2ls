# Mega EverDrive Tools (med2ls)
Представляю маленькую "библиотечку" с примером ее применения в виде проекта VS-Code в рамках программирования для Sega MegaDrive|Genesis с использованием SGDK и отладки плодов своего творчества в аппаратной среде посредствам Mega EverDrive v2 (X7).

Использование представленного кода предполагает работу со штатной утилитой загрузки контента Mega EverDrive - утилитой  [mega-usb](https://github.com/MiGeRA/Mega-EverDrive-Uploader).

Системное ПО EverDrive ("системный картридж" - MEGA.BIN) допускает передачу и запуск программ (внезапно?) через USB-соединение - утилита mega-usb в помощь. При запуске программы (игры) USB-соединение полностью переходит под управление данной запущенной программы, подавляющее большинство которых не использует его (даже не догадываясь о таком досадном моменте) - соответственно для запуска новой программы (обновленной версии текущей) необходимо вернуться в главное меню системного ПО EverDrive. Путей несколько: "передернуть" питание; жамкнуть "ресет" на приставке; воспользоваться "внутриигровым" меню EverDrive (DOWN+START) ... Все они предусматривают тактильное взаимодействие либо с самой приставкой, либо с ее джойстиком. В случае создания и отладки софта "в железе" с использованием возможности его загрузки через USB-соединение EverDrive видится логичным и удобным реализация программной возможности возврата в главное меню по команде через USB-соединение для последующей аналогичной загрузки ...

Простое включение библиотеки **med2ls** в ваш проект SGDK дает следующие ...
#### Возможности:
+ Загружать обновленную (вновь скомпиллированную версию, например) без физического взаимодействия с приставкой. Все управление чисто по USB-интерфейсу. Т.е. не нужно жать RESET чтобы вернуться в главное меню EverDrive для возможности повторной загрузки и запуска программы - просто инициируйте штатный процесс передачи-запуска программы в mega-usb поверх уже запущенной;
+ Осуществлять возврат (выход) в главное меню EverDrive из вашей программы по комбинации "горячих клавиш" (в предложенном варианте START+A+B+C - легко изменить при желании);
+ Возврат в главное меню EverDrive по управляющей последовательности, получаемой через USB-соединение;
+ Возможность реализовать выход в главное меню EverDrive в любом месте вашей программы на ваше усмотрение ("программный выход" - логичная тривиальная функция, совместима любым аппаратным картриджем).

#### Использовать так:
В любом случае копируем в доступное проекту место файлы med2ls.c и med2ls.h, делаем включение в модуле main:
```
#include "med2ls.h"
```

Для реализации первых трех пунктов "возможностей" - просто добавляем в основной бесконечный цикл вызов:
```
MED2ls_RetWacthDog();
```

Для пользовательского возврата - пишем в нужном месте:
```
MED2ls_Return();
```

Все просто ... :-)

*PS. Учесть, что для взаимодействия по USB-соединению при использовании Mega EverDrive совместно с утилитой mega-usb (и не только) **необходимо активировать режим -ssf** *
