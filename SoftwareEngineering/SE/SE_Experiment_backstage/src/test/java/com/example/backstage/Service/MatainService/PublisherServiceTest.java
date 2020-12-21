package com.example.backstage.Service.MatainService;

import com.example.backstage.Entity.CatalogueEntity.Temporary;
import com.example.backstage.Entity.MaintainEntity.Publisher;
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

/** 
* PublisherService Tester. 
* 
* @author 罗驰
* @since <pre>6月 22, 2020</pre>
* @version 1.0 
*/ 
@RunWith(SpringRunner.class)
@SpringBootTest
@WebAppConfiguration
@Log4j2
public class PublisherServiceTest {
    @Autowired
    private PublisherService service;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: findPublisherByName(String name) 
* 
*/ 
@Test
public void testFindPublisherByName() throws Exception { 
//TODO: Test goes here...
    log.info(service.findPublisherByName(""));
} 

/** 
* 
* Method: addPublisher(Publisher publisher) 
* 
*/ 
@Test
public void testAddPublisher() throws Exception { 
//TODO: Test goes here...
    Publisher publisher=new Publisher("ccc","aaa","123");
    service.addPublisher(publisher);
}

/** 
* 
* Method: findPublisherByPhone(String number) 
* 
*/ 
@Test
public void testFindPublisherByPhone() throws Exception { 
//TODO: Test goes here...
    log.info(service.findPublisherByPhone("123"));
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
    Page<Publisher> list=service.findAllByPage("",pageable);
    log.info(list.getContent());
} 

/** 
* 
* Method: findAllIdName(String name) 
* 
*/ 
@Test
public void testFindAllIdName() throws Exception { 
//TODO: Test goes here...
    log.info(service.findAllIdName(""));
} 

/** 
* 
* Method: deleteById(int id) 
* 
*/ 
@Test
public void testDeleteById() throws Exception { 
//TODO: Test goes here...
    service.deleteById(9);
} 


} 
