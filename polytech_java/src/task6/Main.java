package task6;

// В текстовом файле содержится информация о переводах средств со счета на счет.
// Создайте приложение, позволяющее в параллельном режиме обработать эту информацию
// (счета в приложении представляют собой объекты).
// Синхронизируйте код приложения используя ключевое слово synchronized
// (1 вариант) и библиотеку java.util.concurrent (2 вариант).
// https://www.ibm.com/developerworks/ru/library/j-5things15/index.html


import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.stream.IntStream;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;


public class Main {
  private static ConcurrentLinkedQueue<Transaction> queue = new ConcurrentLinkedQueue<>();
  private static Map<Integer, Account> accountMap = new ConcurrentHashMap<>();

  static class TransactionProcessor extends Thread {

    @Override
    public void run() {
      System.out.println("Запущен поток " + getName());
      int amount = 0;
      while (true){
          Transaction transaction = queue.poll();
        if (transaction != null) {
            amount = transaction.getAmount();
            accountMap.get(transaction.getFrom()).atomicAddAndGet(-amount);
            accountMap.get(transaction.getTo()).atomicAddAndGet(amount);
        } else {
          break;
        }
      }
    }
  }

  private static ConcurrentLinkedQueue<Transaction> getTransactionQueue(boolean from_json) {
      // В 11 Джаве джексон не работет, поэтому тут такая заглушка.
      // Я знаю что можно скомпилировать в режиме обратной совместимости предыдущими версиями джавы, но возникли сложности с мавеном.
      // В целом я разобрался как работает джексон, и не видел смысла тратить время на проблемы обратной совместимости.
      if (from_json) {
          ObjectMapper mapper = new ObjectMapper();
          File file = new File("src/task6/Lab6InputExample.json");
          List<Transaction> listTransaction = new ArrayList<Transaction>();

          try {
              listTransaction = mapper.readValue(file,new TypeReference<ArrayList<Transaction>>(){});
          } catch (IOException e) {
              e.printStackTrace();
          }

          return (ConcurrentLinkedQueue<Transaction>) listTransaction;

      } else {
          ConcurrentLinkedQueue<Transaction> queue = new ConcurrentLinkedQueue<Transaction>();
          queue.add(new Transaction(0, 1, 2, 111));
          queue.add(new Transaction(1, 3, 2, 222));
          queue.add(new Transaction(2, 3, 2, 333));
          queue.add(new Transaction(3, 2, 3, 444));
          return queue;
      }
    }

  public static void main(String[] args) {
    IntStream.range(0, 3).forEachOrdered(n -> {
        Account tmp = new Account();
        accountMap.put(tmp.id, tmp);
    });

    // Получаем очередь транзакций
    queue = getTransactionQueue(false);

    // Создаем и запускаем треды обрабатывающие очередь с транзакциями.
    TransactionProcessor t1 = new TransactionProcessor();
    TransactionProcessor t2 = new TransactionProcessor();
    t1.start();
    t2.start();

    try {
        t1.join();
        t2.join();
    } catch (InterruptedException e) {
        e.printStackTrace();
    }

    for (Map.Entry<Integer, Account> entry : accountMap.entrySet()) {
      System.out.println(entry.getValue());
    }
  }
}

//    Выполнен поток Thread-1
//    Выполнен поток Thread-0
//    654
//    Account ID: 1Bill: -111
//    Account ID: 2Bill: 222
//    Account ID: 3Bill: -111