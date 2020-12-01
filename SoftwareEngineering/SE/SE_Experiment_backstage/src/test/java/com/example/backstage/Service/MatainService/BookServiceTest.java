package com.example.backstage.Service.MatainService;

import com.example.backstage.Entity.CatalogueEntity.Temporary;
import com.example.backstage.Entity.MaintainEntity.Book;
import lombok.extern.log4j.Log4j2;
import org.junit.Test;
import org.junit.Before; 
import org.junit.After; 
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.web.WebAppConfiguration;

import java.util.Date;

/** 
* BookService Tester. 
* 
* @author 罗驰
* @since <pre>6月 28, 2020</pre> 
* @version 1.0 
*/ 
@RunWith(SpringRunner.class)
@SpringBootTest
@WebAppConfiguration
@Log4j2
public class BookServiceTest {
    @Autowired
    private BookService service;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: findAllByPage(String name, Pageable pageable) 
* 
*/ 
@Test
public void testFindAllByPage() throws Exception { 
//TODO: Test goes here...
    Pageable pageable=new PageRequest(0,10);
    Page<Book> list=service.findAllByAll("",pageable);
    log.info(list.getContent());
} 

/** 
* 
* Method: updateBook(Book book) 
* 
*/ 
@Test
public void testUpdateBook() throws Exception { 
//TODO: Test goes here...
    Book book=new Book("1234567890123","yesok",1,"ddd",true,"ddd","2017-02-05",10,"");
    service.updateBook(book);
} 

/** 
* 
* Method: findAllByAuthor(String name, Pageable pageable) 
* 
*/ 
@Test
public void testFindAllByAuthor() throws Exception { 
//TODO: Test goes here...
    Pageable pageable=new PageRequest(0,10);
    Page<Book> list=service.findAllByAuthor("",pageable);
    log.info(list.getContent());
} 

/** 
* 
* Method: findAllByAll(String name, Pageable pageable) 
* 
*/ 
@Test
public void testFindAllByAll() throws Exception { 
//TODO: Test goes here...
    Pageable pageable=new PageRequest(0,10);
    Page<Book> list=service.findAllByAll("",pageable);
    log.info(list.getContent());
} 

/** 
* 
* Method: findByIsbn(String isbn) 
* 
*/ 
@Test
public void testFindByIsbn() throws Exception { 
//TODO: Test goes here...
    log.info(service.findByIsbn("1234567890123"));
} 

/** 
* 
* Method: deleteByIsnb(String isbn) 
* 
*/ 
@Test
public void testDeleteByIsnb() throws Exception { 
//TODO: Test goes here...
    service.deleteByIsnb("1234567890123");
} 


} 
