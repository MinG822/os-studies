FROM ubuntu:gcc
COPY . /usr/src/C4_Threads
WORKDIR /usr/src/C4_Threads
# RUN gcc -o 4.11 4.11.c
# CMD [ "./4.11", "10"]

# RUN gcc -o 4.12 4.12.c
# CMD [ "./4.12", "10"]

RUN gcc -o signal_handling signal_handling.c
CMD [ "./signal_handling", "10"]

# RUN gcc -o cancelling cancelling.c
# CMD [ "./cancelling", "10"]


