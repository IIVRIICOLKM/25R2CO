package Blog.dto;

import Blog.domain.Article;
import lombok.Getter;

//DTO는 엔티티가 아니라 id값을 가지지 않고 내용만 가짐.
@Getter
public class ArticleResponse {
    private final String title;
    private final String content;

    public ArticleResponse(Article article){
        this.title = article.getTitle();
        this.content = article.getContent();
    }
}
