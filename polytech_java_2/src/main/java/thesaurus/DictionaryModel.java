package thesaurus;

import javax.persistence.*;


import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.RequiredArgsConstructor;
import lombok.Setter;
import lombok.NonNull;
import lombok.experimental.Accessors;

@Accessors(chain = true)
@Getter
@Setter
@NoArgsConstructor
@RequiredArgsConstructor
@Entity
@Table(name = "dtest")
public class DictionaryModel {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    @NonNull
    private String word;
    @NonNull
    private String explain;

//    Такой конструкто можно заменить на lombok  RequiredArgsConstructor + NonNull для полей
//    public DictionaryModel(String word, String explain) {
//        this.word = word;
//        this.explain = explain;
//    }

    @Override
    public String toString() {
        return "explain='" + explain + '\'';
    }
}