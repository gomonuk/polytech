package thesaurus.messages;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;
import lombok.experimental.Accessors;

import java.util.List;

@Accessors(chain = true)
@Getter
@Setter
@AllArgsConstructor
public class ThesaurusResponse {
    private String operation_status;
    private List<String> explain;
}
