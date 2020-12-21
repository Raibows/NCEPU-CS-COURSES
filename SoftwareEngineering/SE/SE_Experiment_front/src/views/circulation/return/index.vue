<template>
  <div>
    <el-row>
      <el-col :span="14" :offset="5" style="margin-top: 70px;">
        <el-table
          :data="tableData"
          border
          style="width: 100%"
        >
          <el-table-column
            prop="bookName"
            label="书名"
            width="120"
          />
          <el-table-column
            prop="isbn"
            label="ISBN"
            width="120"
          />
          <el-table-column
            prop="borrowDate"
            label="借书时间"
            width="120"
          />
          <el-table-column
            prop="returnDate"
            label="还书日期"
            width="120"
          />
          <el-table-column
            prop="borrowPeriod"
            label="借阅期限"
            width="162"
          />
          <el-table-column
            label="操作"
            width="120"
          >
            <template slot-scope="scope">
              <el-button type="text" size="small" @click="handleClick(scope.row)">还书</el-button>
              <el-button type="text" size="small" @click="openCheckForm(scope.row)">查看</el-button>
            </template>
          </el-table-column>
        </el-table>
      </el-col>
    </el-row>
    <el-row style="margin-top: 20px;">
      <el-col :span="10" :offset="8">
        <el-pagination
          :current-page="currentPage"
          :page-sizes="[5, 10, 20]"
          :page-size="pageSize"
          layout="total, sizes, prev, pager, next, jumper"
          :total="total"
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
        />
      </el-col>
    </el-row>
    <check ref="check" />
  </div>
</template>

<script>
import { searchUnReturn } from '@/api/borrow'
import { onlyReturn } from '@/api/borrow'
import Check from './check'

export default {
  name: 'CatalogueReimbursementCancellation',
  components: { Check },
  data() {
    return {
      keyword: '',
      currentPage: 1,
      pageSize: 5,
      total: 0,
      tableData: []
    }
  },
  computed: {},
  created() {
    this.search()
  },
  methods: {
    search() {
      searchUnReturn({
        stuid: this.$store.getters.userId,
        pageNum: this.currentPage,
        pageSize: this.pageSize
      }).then(response => {
        console.log(response)
        this.tableData = response.data.list,
        this.pageSize = response.data.size,
        this.currentPage = response.data.pageNum,
        this.total = response.data.total
      })
    },
    handleClick(row) {
      onlyReturn({
        isbn: row.isbn,
        stuid: this.$store.getters.userId })
        .then(response => {
          this.search()
          this.$message({
            message: response.msg,
            type: 'success'
          })
        })
    }, handleSizeChange(val) {
      this.pageSize = val
      this.search()
    },
    handleCurrentChange(val) {
      this.currentPage = val
      this.search()
    },
    openCheckForm(row) {
      this.$refs.check.modifyVisible = true
      this.$refs.check.form = row
    }
  }

}
</script>

<style lang="scss" scoped>

</style>
