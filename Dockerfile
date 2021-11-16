FROM python:3

RUN apt-get update

RUN apt install -y clang clang-format
RUN pip install --upgrade pip
RUN pip install --upgrade setuptools

WORKDIR /home/src

COPY . /home/src
RUN pip install -r scripts/requirements.txt

EXPOSE 3000

