package org.sc05.scwebappmall.dto;
import lombok.*;
import org.sc05.scwebappmall.entity.ScWebAppMall;

@Getter
@NoArgsConstructor
@AllArgsConstructor
public class ScWebAppMallDTO {
    private String name;
    private String content;
    private int price;

    public ScWebAppMall toEntity()
    {
        return new ScWebAppMall(name, content, price);
    }
}
