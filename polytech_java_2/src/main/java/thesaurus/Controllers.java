package thesaurus;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import thesaurus.messages.ThesaurusRequest;
import thesaurus.messages.ThesaurusResponse;

import java.util.Collections;


@RestController
public class Controllers {

    @Autowired
    ThesaurusService thesaurus;

    @RequestMapping("/")
    public String index() {
        return "Greetings from Spring Boot!";
    }

    @RequestMapping(value = "/explain", method = RequestMethod.POST)
//    @ResponseBody непонятно что делает
    public ThesaurusResponse add_explain(@RequestBody ThesaurusRequest request) {
        thesaurus.save(request.getWord(), request.getExplain());
        return new ThesaurusResponse("SUCCESS", Collections.singletonList(request.getExplain()));
    }

    @RequestMapping(value = "/explain", method = RequestMethod.GET)
    public ThesaurusResponse get_explain(@RequestParam("word") String word) {
        return new ThesaurusResponse("SUCCESS", thesaurus.get(word));
    }

    // Для мидлвари
    @RequestMapping(value = "/raise", method = RequestMethod.GET)
    public String raise() {
        throw new NullPointerException("test");
    }

}
