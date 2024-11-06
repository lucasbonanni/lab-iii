Como saber si una cola está llena y que tamaño tiene.

void check_message_queue_status(int id_cola_mensajes) {
    struct msqid_ds buf;
    if (msgctl(id_cola_mensajes, IPC_STAT, &buf) == -1) {
        perror("Error getting message queue status");
        return;
    }

    printf("Message queue status:\n");
    printf("  Number of messages: %lu\n", buf.msg_qnum);
    printf("  Total bytes in queue: %lu\n", buf.msg_cbytes);
    printf("  Maximum bytes allowed in queue: %lu\n", buf.msg_qbytes);
}
