# linux-symbol-driver
Символьный драйвер, позволяющий передавать информацию двум независимым процессам по принципу кольцевого буфера

Установка размера кольцевого буфера происходит через механизм параметров модулей ядра.

Возможны запись, чтение в буфер символьного драйвера. По умолчанию данные операции являются блокирующими, но возможно изменение режима (см. вызовы ioctl).

Операции можно отследить при помощи dmesg. 

Тщательное логирование сделано для проверки работоспособности драйвера и должно быть значительно сокращено на практике.

Вызовы ioctl:
1. Установка блокирующего/неблокирующего режима чтения/записи
2. Получение времени (в секундах от старта ОС) последней операции чтения из буфера
3. Получение идентификатора процесса, выполнившего последнюю операцию чтения
4. Получение времени (в секундах от старта ОС) последней операции чтения из буфера
5. Получение идентификатора процесса, выполнившего последнюю операцию записи
6. Получение идентификатора владельца процесса, выполнившего последнюю операцию чтения
7. Получение идентификатора владельца процесса, выполнившего последнюю операцию записи

## Файлы исходного кода
`scdrv.h` - описание модуля

`buffer.h` - структура кольцевого буфера

`scdrv_io.h` - read, write, open, release, ioctl

## Сборка и установка
`./install.sh`

Скрипт запросит ввод размера буфера драйвера. После этого возможен запрос пароля суперпользователя для установки и настройки модуля.

## Ввод/вывод через консоль

`echo abc > /dev/scdrv0`

`cat /dev/scdrv0`

## Проверка работоспособности драйвера
`ls /dev/scdrv0`

`dmesg` (строки "SCDRV:") 

Логирование почти каждой операции драйвера сделано только для отладки, на практике должно быть значительно сокращено.

## Тестирование
В папке test_programs имеются программы test_read.c, test_ioctl.c, test_write.c для проверки работоспособности драйвера

`gcc test_write.c -o write`

`gcc test_read.c -o read`

`gcc test_ioctl.c -o ioctl`

`./write`

`./read`

`./ioctl`


Установку блокирующего режима можно отследить через dmesg

## TODO
All done

## Задача
Реализовать символьный драйвер предлагающий возможность передавать информацию двум независимым процессам 
через файл символьного устройства: 
- взаимодействие должно осуществляться по принципу кольцевого буфера;  т.е. один процесс может писать в файл символьного устройства, а другой из него читать. 
- обеспечить возможность задавать размер кольцевого буфера через механизм параметров модулей ядра; 
- по умолчанию вызовы чтения и записи должны быть блокирующими; 
- обеспечить поддержку нескольких вызовов IOCTL: 
-- переключение режима работы вызовов read\write из блокирующих \ не блокирующих и обратно;
-- обеспечить возможность получения информации о времени последней операции чтения и записи в буфер, а так же идентификаторов и владельцев процессов совершивших эту операцию;

- драйвер должен собираться вне дерева исходных кодов ядра при помощи Makefile; 
- исходные коды драйвера должны находиться под системой контроля версий git и содержать историю коммитов; 
- результат передаётся в виде ссылки на репозиторий размещённый на github или в виде архива содержащего репозиторий с исходными кодами.
