package task6;

import java.util.concurrent.atomic.AtomicInteger;

public class Account {

    int id;
    private static int last_id = 0;
    private AtomicInteger bill = new AtomicInteger(0);
    // надо ли делать bill volatile?
    // Нет не надо:
    // https://stackoverflow.com/questions/19744508/volatile-vs-atomic
    // https://ru.stackoverflow.com/questions/436884/volatile-vs-atomic

    Account() {
        this.id = getLastId();
    }

    private static int getLastId() {
        last_id = last_id + 1;
        return last_id;
    }

    void atomicAddAndGet(int amount) {
        this.bill.addAndGet(amount);
    }

    public String toString() {
        return "Account ID: " + this.id + " Bill: " + this.bill.get();
    }
}
