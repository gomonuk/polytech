package thesaurus;

import org.hibernate.Session;
import org.springframework.stereotype.Service;
import org.hibernate.Transaction;
import thesaurus.utils.HibernateSessionFactoryUtil;

import java.util.List;
import java.util.stream.Collectors;

@Service
public class ThesaurusService {

    public List<String> get(String word) {
        List<DictionaryModel> explainsList = HibernateSessionFactoryUtil
                .getSessionFactory()
                .openSession()
                .createQuery("from DictionaryModel where word like :word")
                .setString("word", "%" + word + "%")
//                .setParameter("word", word)
                .list();
        return explainsList.stream().map(DictionaryModel::getExplain).collect(Collectors.toList());
    }

    public void save(String word, String explain) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx1 = session.beginTransaction();
        session.save(new DictionaryModel(word, explain));
        tx1.commit();
        session.close();
    }

}
