package org.sc05.scwebappmall.repository;

import org.sc05.scwebappmall.entity.ScWebAppMall;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import java.util.List;

@Repository
public interface ScWebAppMallRepository extends JpaRepository<ScWebAppMall, Long>
{
    List<ScWebAppMall> findByName(String name);
    void deleteByName(String name);
}
