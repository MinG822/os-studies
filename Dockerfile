FROM ubuntu
RUN apt-get update && \
    apt-get -y install gcc && \
    apt-get install bash