package org.sc05.scwebappmall.config;

import com.sun.jna.platform.win32.Variant;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.builders.PathSelectors;
import springfox.documentation.builders.RequestHandlerSelectors;
import springfox.documentation.spi.DocumentationType;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2;

@Configuration
@EnableSwagger2
public class SwaggerConfig {
@Bean
    public Docket api() {
    return new Docket(DocumentationType.SWAGGER_2)
            .select()
            /* 경로에 있는 컨트롤러들 선택(컨트롤러의 리퀘스트 식별 후 문서화 대상 결정)*/
            .apis(RequestHandlerSelectors.basePackage("org.sc05.scwebappmall.controller"))
            /* 모든 컨트롤러 선택 후 문서화 */
            .paths(PathSelectors.any())
            .build();
}
}
