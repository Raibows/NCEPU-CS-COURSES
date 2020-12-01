package com.example.backstage.Service.InterviewService;

import com.example.backstage.Entity.CatalogueEntity.Temporary;
import com.example.backstage.Entity.InterviewEntity.Refund;
import lombok.extern.log4j.Log4j;
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
* RefundService Tester. 
* 
* @author 罗驰
* @since <pre>6月 22, 2020</pre>
* @version 1.0 
*/ 
@RunWith(SpringRunner.class)
@SpringBootTest
@WebAppConfiguration
@Log4j2
public class RefundServiceTest {
    @Autowired
    private RefundService service;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: addRefund(Refund refund) 
* 
*/ 
@Test
public void testAddRefund() throws Exception { 
//TODO: Test goes here...
    Refund refund=new Refund("1234567891111","201709000616",new Date(),new BigDecimal(20),
            "ss",10,false,"");
    service.addRefund(refund);
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
    Page<Refund> list=service.findAllByPage("",pageable);
    log.info(list.getContent());
} 


} 
