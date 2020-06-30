package task6;

public class Transaction {

    private int id;
    private int from;
    private int to;
    private int amount;

    Transaction(int id, int from, int to, int amount) {
        this.id = id;
        this.from = from;
        this.to = to;
        this.amount = amount;
    }
    // Геттеры и сеттеры были сделаны для джексона. Тогда ещё не знал про ломбок.

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getFrom() {
        return from;
    }

    public void setFrom(int from) {
        this.from = from;
    }

    public int getTo() {
        return to;
    }

    public void setTo(int to) {
        this.to = to;
    }

    public int getAmount() {
        return amount;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }
}
