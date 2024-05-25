package org.sc05.scwebappmall.entity;

import jakarta.persistence.*;
import lombok.*;

@Getter
@NoArgsConstructor(access = AccessLevel.PROTECTED)
@Entity
public class ScWebAppMall {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)

    @Column(name = "id", updatable = false)
    private long id;
    @Column(name = "name", nullable = false)
    private String name;
    @Column(name = "content", nullable = false)
    private String content;
    @Column(name = "price", nullable = false)
    private int price;

    public ScWebAppMall(String name, String content, int price)
    {
        this.name = name;
        this.content = content;
        this.price = price;
    }
}
