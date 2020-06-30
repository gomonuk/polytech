package thesaurus.messages;

import lombok.Getter;
import lombok.Setter;
import lombok.experimental.Accessors;

@Accessors(chain = true)
@Getter
@Setter
public class ThesaurusRequest {
    private String word;
    private String explain;
}


