package com.example.backstage.Dao.MaintainDao;

import com.example.backstage.Entity.MaintainEntity.Book;
import com.example.backstage.Entity.MaintainEntity.Publisher;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface PublisherDao extends JpaRepository<Publisher,String> {
    /**
     *
     * @param name
     * @return
     */
      List<Publisher> findByPublisherNameLike(String name);

    /**
     *
     * @param number
     * @return
     */
      Publisher findByPhoneNumber(String number);

    /**
     *
     * @param name
     */
    void deleteByPublisherName(String name);

    /**
     *
     * @return
     */
    @Query(value = "select * from publisher where publisherName like "+"%"+":name"+"%",nativeQuery = true)
    Page<Publisher> findAllByPage(@Param("name")String name, Pageable pageable);

    /**
     *
     * @return
     */
    @Query(value = "select * from publisher where publisherName like "+"%"+":name"+"%",nativeQuery = true)
    List<Publisher> findAllIdName(@Param("name")String name);

    /**
     *
     * @param id
     */
     void deleteById(int id);

}
