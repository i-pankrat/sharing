# Sharing

Сервис предоставляет возможность для регистрации приложений или иных сервисов с целью их дальнейшего использования для открытия файлов различных форматов. 

Сервис зарегистрирован на сессионой шине DBUS и предоставляет API для:

* Регистрации приложения
* Добавления поддерживаемых форматов файлов приложения
* Получения строки, позволяющей открыть файл определённого формата в приложении

# Как собрать

Данный раздел объясняет процесс cборки и установки

## Установить через deb пакет

1. Необходимо установить:
    * libqt5core5a
    * libqtdbys5
2. Скачать deb пакет из [релиза](https://github.com/i-pankrat/sharing/releases)
3. Установить sharing. Сервис устанавливается в **/home**
```bash
$ sudo dpkg -i sharing_0.1.0-1_amd64.deb
```

## Как собрать из исходников 

Зависимости:

* g++
* cmake
* Qt Core и Qt D-Bus (>= 5)

Сборка:
```bash
$ cmake -B build
$ cmake --build build/
```

# API

В данном разделе будут описаны имеющиеся API методы, и будут показаны примеры их использования. Все примеры используют утилиту [dbus-send](https://dbus.freedesktop.org/doc/dbus-send.1.html).

* Регистрация приложения "code" в сервисе
```bash
$ dbus-send --session --print-reply --type=method_call --dest=ru.pankrat.Sharing / ru.pankrat.Sharing.registerApp string:'code'
```

* Получение информации о всех зарегистрированных приложениях

```bash
$ dbus-send --session --print-reply --type=method_call --dest=ru.pankrat.Sharing / ru.pankrat.Sharing.getRegisteredApps

array [
    string "code"
]
```

* Добавление поддерживаемого формата "cpp" в приложение "code"

```bash
$ dbus-send --session --print-reply --type=method_call --dest=ru.pankrat.Sharing / ru.pankrat.Sharing.addFileType string:'code' string:'cpp'
```

* Получение всех поддерживаемых в приложении "code" форматов

```bash
$ dbus-send --session --print-reply --type=method_call --dest=ru.pankrat.Sharing / ru.pankrat.Sharing.getAvailableFileTypes string:'code'

array [
    string "cpp"
    string "c"
    string "h"
]
```

* Добавление способа, с помощью которого можно открыть файл определённого формата в приложении "code". Важно, что последний аргумент запроса, содержит собой строку, которая должна будет выполнить необходимо действие, если её ввести в терминале. При этом в этой строке обязательно должна быть подстрока '%file', вместо которой подставится название файла.

```bash
$ dbus-send --session --print-reply --type=method_call --dest=ru.pankrat.Sharing / ru.pankrat.Sharing.addOpenWay string:'code' string:'code %file'
``` 

* Получение строки, выполнив которую в терминале можно запустить необходимый файл из приложения "code".

```bash
$ dbus-send --session --print-reply --type=method_call --dest=ru.pankrat.Sharing / ru.pankrat.Sharing.open string:'code' string:'cpp' string:'main.cpp'

string "code main.cpp"
``` 

* Интроспекция
```bash
$ dbus-send --session --print-reply --dest=ru.pankrat.Sharing --type=method_call / org.freedesktop.DBus.Introspectable.Introspect
```
