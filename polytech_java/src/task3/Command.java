package task3;

abstract class Command {

    StringBuilder string_builder;

    Command(StringBuilder string_builder) {
        this.string_builder = string_builder;
    }

    public abstract StringBuilder execute();
}

class AppendCommand extends Command {
    private final Object object;

    AppendCommand(StringBuilder string_builder, Object object) {
        super(string_builder);
        this.object = object;
    }

    @Override
    public StringBuilder execute() {
        return string_builder.append(this.object);
    }
}


class ReverseCommand extends Command {
    ReverseCommand(StringBuilder string_builder) {
        super(string_builder);
    }

    @Override
    public StringBuilder execute() {
        return string_builder.reverse();
    }
}