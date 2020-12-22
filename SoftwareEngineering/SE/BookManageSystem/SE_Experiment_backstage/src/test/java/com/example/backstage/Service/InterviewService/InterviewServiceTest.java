package com.example.backstage.Service.InterviewService;

import com.example.backstage.Entity.InterviewEntity.Interview;
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

import java.math.BigDecimal;
import java.util.Date;

/** 
* InterviewService Tester. 
* 
* @author 罗驰
* @since <pre>6月 22, 2020</pre>
* @version 1.0 
*/ 
@RunWith(SpringRunner.class)
@SpringBootTest
@WebAppConfiguration
@Log4j2
public class InterviewServiceTest {
    @Autowired
    private InterviewService service;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: addInterview(Interview interview) 
* 
*/ 
@Test
public void testAddInterview() throws Exception { 
//TODO: Test goes here...
    Interview interview=new Interview("1000","201709000616","abc",new BigDecimal(20),
            new Date(),"1234567891111","ddd",10,"");
    service.addInterview(interview);
} 

/** 
* 
* Method: findInterviewById(String id) 
* 
*/ 
@Test
public void testFindInterviewById() throws Exception { 
//TODO: Test goes here...
    log.info(service.findInterviewById("1000"));
} 

/** 
* 
* Method: findAll(String name, Pageable pageable) 
* 
*/ 
@Test
public void testFindAll() throws Exception { 
//TODO: Test goes here...
    Pageable pageable=new PageRequest(0,10);
    Page<Interview> list=service.findAll("",pageable);
    log.info(list.getContent());
} 

/** 
* 
* Method: deleteById(String id) 
* 
*/ 
@Test
public void testDeleteById() throws Exception { 
//TODO: Test goes here...
    service.deleteById("1000");
} 

/** 
* 
* Method: deleteByIsbn(String isbn) 
* 
*/ 
@Test
public void testDeleteByIsbn() throws Exception { 
//TODO: Test goes here...
    service.deleteByIsbn("1234567891111");
} 


} 
