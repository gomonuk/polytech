package task3;

import java.util.Stack;

// Напишите свой класс StringBuilder с поддержкой операции undo.
// Для этого делегируйте все методы стандартному StringBuilder,
// а в собственном классе храните список всех операций для выполнения undo().
// Это будет реализацией шаблона «Команда».


class MyStringBuilder {

    private StringBuilder string_builder = new StringBuilder();
    private Stack<StringBuilder> backup_stack = new Stack<>();

    @Override
    public String toString() {
        return String.valueOf(string_builder);
    }

    void append(Object object) {
        Command tmp = new AppendCommand(string_builder, object);
        tmp.execute();
        backup(string_builder);
    }

    void reverse(){
        Command r = new ReverseCommand(string_builder);
        r.execute();
        backup(string_builder);
    }

    private void backup(StringBuilder s) {
        backup_stack.push(new StringBuilder(s));
    }

    void undo() {
        backup_stack.pop();
        string_builder = backup_stack.lastElement();
    }
}

public class Main {
    public static void main(String[] args) {
        MyStringBuilder s = new MyStringBuilder();
        s.append("a");
        s.append("b");
        s.append("c");
        System.out.println(s);

        s.undo();
        System.out.println(s);

        s.append("c");
        System.out.println(s);

        s.reverse();
        System.out.println(s);

        s.undo();
        System.out.println(s);
    }
}
