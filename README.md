## Laboratory work 8.

Данная лабораторная работа посвещена изучению систем автоматизации развёртывания и управления приложениями на примере Docker

```bash
# переходим в каталог рабочей среды, добавляем текущий каталог в стек (pushd), активируем скрипт scripts/active, где находятся параметры и переменные имена, которые могут понадобиться. 
cd ${GITHUB_USERNAME}/workspace
pushd .
source scripts/activate
```

```bash
# клонируем репозиторий, обновляем модули
git clone https://github.com/${GITHUB_USERNAME}/lab07 projects/lab08
cd projects/lab08
git remote remove origin
git remote add origin https://github.com/${GITHUB_USERNAME}/lab08
```

```bash
# создаём докер файл
cat > Dockerfile <<EOF
FROM ubuntu:18.04
EOF
```

```bash
# добавляем, что он обновиться и поставит компилятор gcc и cmake
cat >> Dockerfile <<EOF

RUN apt update
RUN apt install -yy gcc g++ cmake
EOF
```

```bash
# добавляем, что скопирует print и будет считать её за workdir (рабочий каталог контейнеара)

cat >> Dockerfile <<EOF

COPY . print/
WORKDIR print
EOF
```

```bash
# добавляем в докер сборку cmake проекта
cat >> Dockerfile <<EOF

RUN cmake -H. -B_build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=_install
RUN cmake --build _build
RUN cmake --build _build --target install
EOF
```

```bash
# задаём докеру пути для логов
cat >> Dockerfile <<EOF

ENV LOG_PATH /home/logs/log.txt
EOF
```

```bash
# создаём том для загрузки контейнера
cat >> Dockerfile <<EOF

VOLUME /home/logs
EOF
```

```bash
# устанавливаем _install/bin как workdir
cat >> Dockerfile <<EOF

WORKDIR _install/bin
EOF
```

```bash
# указываем точку входа
cat >> Dockerfile <<EOF

ENTRYPOINT ./demo
EOF
```

```bash
# сборка внутри докера
docker build -t logger .
```

OUTPUT:
```
[+] Building 187.5s (14/14) FINISHED                                                                                                                                               docker:default
 => [internal] load build definition from Dockerfile                                                                                                                                         0.0s
 => => transferring dockerfile: 379B                                                                                                                                                         0.0s
 => [internal] load metadata for docker.io/library/ubuntu:24.10                                                                                                                              1.3s
 => [internal] load .dockerignore                                                                                                                                                            0.0s
 => => transferring context: 2B                                                                                                                                                              0.0s
 => [1/9] FROM docker.io/library/ubuntu:24.10@sha256:aadf9a3f5eda81295050d13dabe851b26a67597e424a908f25a63f589dfed48f                                                                        0.0s
 => [internal] load build context                                                                                                                                                            0.1s
 => => transferring context: 57.10kB                                                                                                                                                         0.1s
 => CACHED [2/9] RUN apt update                                                                                                                                                              0.0s
 => CACHED [3/9] RUN apt install -yy gcc g++ cmake                                                                                                                                           0.0s
 => [4/9] COPY . print/                                                                                                                                                                      0.2s
 => [5/9] WORKDIR print                                                                                                                                                                      0.0s
 => [6/9] RUN cmake -H. -B_build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=_install                                                                                                177.1s
 => [7/9] RUN cmake --build _build                                                                                                                                                           1.7s 
 => [8/9] RUN cmake --build _build --target install                                                                                                                                          0.5s 
 => [9/9] WORKDIR _install/bin                                                                                                                                                               0.1s 
 => exporting to image                                                                                                                                                                       6.5s 
 => => exporting layers                                                                                                                                                                      6.5s 
 => => writing image sha256:56711956d169d022091d0be9f8b0f5ac07818cb3df0acdb1b9d10be0d0bc353b                                                                                                 0.0s 
 => => naming to docker.io/library/logger                                                                                                                                                    0.0s 

 3 warnings found (use docker --debug to expand):
 - WorkdirRelativePath: Relative workdir "print" can have unexpected results if the base image changes (line 7)
 - LegacyKeyValueFormat: "ENV key=value" should be used instead of legacy "ENV key value" format (line 13)
 - JSONArgsRecommended: JSON arguments recommended for ENTRYPOINT to prevent unintended behavior related to OS signals (line 19)
```

```bash
# выведем образы
docker images
```
OUTPUT:
```
REPOSITORY   TAG       IMAGE ID       CREATED              SIZE
logger       latest    56711956d169   About a minute ago   504MB
```

```bash
# создадим каталог logs и запустим докер
mkdir logs
docker run -it -v "$(pwd)/logs/:/home/logs/" logger
```

```bash
# выводим всё, что известно о контейнере logger
docker inspect logger
```

```bash
# выводим логи
cat logs/log.txt
```

```bash
# меняем в ридми lab07 на lab08 везде
gsed -i 's/lab07/lab08/g' README.md
```

```bash
# редактируем тревис конфиг через vim
vim .travis.yml
services:
- docker
script:
- docker build -t logger .
:wq
```

```bash
# добавляем докерфайл, тревис, коммитим и отправляем результат
git add Dockerfile
git add .travis.yml
git commit -m"adding Dockerfile"
git push origin master
```

Output:

```
[master 2362f4b] adding Dockerfile
 2 files changed, 22 insertions(+)
 create mode 100644 Dockerfile

Enumerating objects: 866, done.
Counting objects: 100% (866/866), done.
Delta compression using up to 24 threads
Compressing objects: 100% (264/264), done.
Writing objects: 100% (866/866), 545.09 KiB | 136.27 MiB/s, done.
Total 866 (delta 584), reused 860 (delta 582), pack-reused 0
remote: Resolving deltas: 100% (584/584), done.
remote: 
remote: Create a pull request for 'master' on GitHub by visiting:
remote:      https://github.com/Gigachader007/lab08/pull/new/master
remote: 
To https://github.com/Gigachader007/lab08
 * [new branch]      master -> master
```
