#include "transport.h"

const char* FILENAME = (char*)"data.txt";   // Указание на именя файла для хранения данных
Transport* transports = NULL;               // Указатель на массив структур
int transport_count = 0;                    // Фактическое количество ТС
int transport_capacity = 0;                 // Вместимость массива


// Инициализация транспортной системы
void TransportSystem()
{
    transport_capacity = 100;                                                   // Начальная вместительность массива
    transports = (Transport*)malloc(transport_capacity * sizeof(Transport)); 

    for (int i = 0; i < transport_capacity; i++)
    {
        (*(transports + i)).bookings = NULL; 
        (*(transports + i)).booking_count = 0; 
    }
}

// Увеличение памяти
void ensureCapacity()
{
    if (transport_count >= transport_capacity) 
    {
        transport_capacity *= 2; 
        Transport* new_transports = (Transport*)realloc(transports, transport_capacity * sizeof(Transport)); 
        if (new_transports) 
        {
            transports = new_transports; 
        }
    }
}

// Очистка памяти 
void cleanupTransportSystem()
{
    if (transports) 
    {
        for (int i = 0; i < transport_count; i++) 
        {
            if ((*(transports + i)).bookings) 
            {
                free((*(transports + i)).bookings); 
            }
        }
        free(transports); 
        transports = NULL; 
    }
    transport_count = 0; 
    transport_capacity = 0; 
}

// Проверка корректности данных о транспортах
void validateTransportData()
{

    for (int i = 0; i < transport_count; i++)
    {
        // Проверка id
        if ((*(transports + i)).id <= 0) 
        {
            (*(transports + i)).id = i + 1; 
        }

        // Проверка типа
        if ((*(transports + i)).type != TRUCK && (*(transports + i)).type != PASSENGER) 
        {
            (*(transports + i)).type = TRUCK; 
        }

        // Проверка модели
        if (strlen((*(transports + i)).model) == 0) 
        {
            strcpy_s((*(transports + i)).model, sizeof((*(transports + i)).model), "Unknown"); 
        }

        // Проверка вместительности
        if ((*(transports + i)).capacity < 0) 
        {
            (*(transports + i)).capacity = 0; 
        }

        // Проверка количества 
        if ((*(transports + i)).available < 0) 
        {
            (*(transports + i)).available = 0; 
        }

        // Проверка статуса
        if (strlen((*(transports + i)).current_status) == 0) 
        {
            strcpy_s((*(transports + i)).current_status, sizeof((*(transports + i)).current_status), "Available"); 
        }
    }
}

// Доступность 
int isVehicleAvailable(int id, const char* date)
{
    for (int i = 0; i < transport_count; i++)
    {
        if ((*(transports + i)).id == id) 
        {
            for (int j = 0; j < (*(transports + i)).booking_count; j++) 
            {
                if (strcmp((*(transports + i)).bookings[j].date, date) == 0) 
                {
                    return 0; 
                }
            }
            return 1; 
        }
    }
    return 0; 
}

// Бронирование ТС
void orderTransport()
{
    char input[MAX_STRING];                 // Буфер для ввода 
    int day, month, year, hour, minute;     // Переменные для хранения даты и времени
    char user[MAX_STRING];                  // Имя заказчика
    int found = 0;                          // Флаг, найден транспорт
    int search_by_id = 0;                   // Флаг, поиска по ID
    int id = 0;                             // Переменная для хранения ID

    printf("\nBook a Vehicle\nEnter vehicle ID or model: "); 
    if (fgets(input, sizeof(input), stdin) == NULL) 
    {
        return;
    }
    input[strcspn(input, "\n")] = '\0'; 

    char* endptr;
    id = strtol(input, &endptr, 10); 
    if (*endptr == '\0') search_by_id = 1; 

    for (int i = 0; i < transport_count; i++) 
    {
        // Поиск по ID или модели
        if ((search_by_id && (*(transports + i)).id == id) ||
            (!search_by_id && strcmp((*(transports + i)).model, input) == 0))
        {
            found = 1; 

            if ((*(transports + i)).available <= 0) 
            {
                printf("No available vehicles of this type\n"); 
                return;
            }

            
            do 
            {
                printf("Enter booking date (DD.MM.YYYY): "); 
                if (scanf_s("%d.%d.%d", &day, &month, &year) != 3) 
                {
                    while (getchar() != '\n'); 
                    printf("Invalid date format\n");
                    continue; 
                }
                while (getchar() != '\n'); 
            } while (!isValidDate(day, month, year)); 

            
            char date_str[20];
            sprintf_s(date_str, sizeof(date_str), "%02d.%02d.%04d", day, month, year); 

            // Проверка доступности ТС на заданную дату
            if (!isVehicleAvailable((*(transports + i)).id, date_str))
            {
                printf("This vehicle is already booked on %s\n", date_str); 
                return;
            }

            
            do
            {
                printf("Enter booking time (HH:MM): "); 
                if (scanf_s("%d:%d", &hour, &minute) != 2) 
                {
                    while (getchar() != '\n');
                    printf("Invalid time format\n"); 
                    continue;
                }
                while (getchar() != '\n'); 
            } while (!isValidTime(hour, minute)); 

            char time_str[10];
            sprintf_s(time_str, sizeof(time_str), "%02d:%02d", hour, minute); 

            printf("Enter your name: "); 
            if (fgets(user, sizeof(user), stdin) == NULL) 
            {
                return; 
            }
            user[strcspn(user, "\n")] = '\0'; 


            (*(transports + i)).booking_count++;

            Booking* new_bookings = (Booking*)realloc((*(transports + i)).bookings,
                (*(transports + i)).booking_count * sizeof(Booking));
            if (new_bookings)
            {
                (*(transports + i)).bookings = new_bookings; 
            }
            else
            {
                printf("Memory allocation failed\n"); 
                return;
            }

            // Копирование даты, времени и имя пользователя в новое бронирование
            strcpy_s((*(transports + i)).bookings[(*(transports + i)).booking_count - 1].date,
                sizeof((*(transports + i)).bookings[0].date), date_str);
            strcpy_s((*(transports + i)).bookings[(*(transports + i)).booking_count - 1].time,
                sizeof((*(transports + i)).bookings[0].time), time_str);
            strcpy_s((*(transports + i)).bookings[(*(transports + i)).booking_count - 1].user,
                sizeof((*(transports + i)).bookings[0].user), user);

            (*(transports + i)).available--; 
            strcpy_s((*(transports + i)).current_status,
                sizeof((*(transports + i)).current_status), "Booked"); 


            printf("Successfully booked %s (ID: %d) on %s at %s\n",
                (*(transports + i)).model, (*(transports + i)).id, date_str, time_str);

            saveToFile(); 
            return; 
        }
    }

    if (!found) printf("Vehicle not found!\n");
}

// Отмена бронирования 
void cancelBooking() 
{
    char input[MAX_STRING];               // Буфер для ввода 
    int found = 0;                        // Флаг, найден ли транспорт
    int search_by_id = 0;                 // Флаг, для поиска
    int id = 0;                           // Переменная для хранения ID 
    int booking_num;                      // Переменная для номера бронирования

    printf("\nCancel Booking\nEnter vehicle ID or model: ");  
    fgets(input, sizeof(input), stdin);   
    input[strcspn(input, "\n")] = '\0'; 

    char* endptr;                        
    id = strtol(input, &endptr, 10);    
    if (*endptr == '\0') search_by_id = 1;  

    for (int i = 0; i < transport_count; i++) 
    {
        if ((search_by_id && (*(transports + i)).id == id) ||   
            (!search_by_id && strcmp((*(transports + i)).model, input) == 0))  
        {
            found = 1;                    

            if ((*(transports + i)).booking_count == 0)  
            {
                printf("No bookings found for this vehicle\n");  
                return;                  
            }

            printf("\nCurrent bookings for %s (ID: %d):\n", (*(transports + i)).model, (*(transports + i)).id);  
            for (int j = 0; j < (*(transports + i)).booking_count; j++)  
            {
                printf("%d. Date: %s, Time: %s, User: %s\n",
                    j + 1, (*(transports + i)).bookings[j].date,
                    (*(transports + i)).bookings[j].time, (*(transports + i)).bookings[j].user); 
            }


            printf("Enter booking number to cancel: ");  
            scanf_s("%d", &booking_num);   
            while (getchar() != '\n');     

            if (booking_num < 1 || booking_num >(*(transports + i)).booking_count)  
            {
                printf("Invalid booking number\n");  
                return;                    
            }

           
            for (int j = booking_num - 1; j < (*(transports + i)).booking_count - 1; j++)  
            {
                (*(transports + i)).bookings[j] = (*(transports + i)).bookings[j + 1];  
            }
            (*(transports + i)).booking_count--;  
            (*(transports + i)).available++;      

            if ((*(transports + i)).booking_count == 0)  
            {
                strcpy_s((*(transports + i)).current_status, "Available"); 
            }

            printf("Booking cancelled successfully\n");  
            saveToFile();                   
            return;                       
        }
    }

    if (!found) printf("Vehicle not found!\n");  
}


// Редактирование бронирования
void editBooking()
{
    char input[MAX_STRING];                // Буфер для ввода 
    int found = 0;                         // Флаг, найден ли транспорт
    int search_by_id = 0;                  // Флаг, поиска  по ID или по модели 
    int id = 0;                            // Переменная для хранения ID 
    int booking_num;                       // Переменная для номера бронирования 
    int day, month, year, hour, minute;    // Переменные для хранения даты и времени
    char date_input[20];                   // Буфер для даты
    char new_date[20];                     // Буфер для новой даты
    char time_input[10];                   // Буфер для времени
    char new_time[10];                     // Буфер для нового времени

    printf("\nEdit Booking\nEnter vehicle ID or model: ");  
    fgets(input, sizeof(input), stdin);   
    input[strcspn(input, "\n")] = '\0';  

    char* endptr;                        
    id = strtol(input, &endptr, 10);     
    if (*endptr == '\0') search_by_id = 1;  

    for (int i = 0; i < transport_count; i++)  
    {
        if ((search_by_id && (*(transports + i)).id == id) ||  
            (!search_by_id && strcmp((*(transports + i)).model, input) == 0)) 
        {
            found = 1;                   

            if ((*(transports + i)).booking_count == 0) 
            {
                printf("No bookings found for this vehicle\n");  
                return;                  
            }

            printf("\nCurrent bookings for %s (ID: %d):\n", (*(transports + i)).model, (*(transports + i)).id);  
            for (int j = 0; j < (*(transports + i)).booking_count; j++)  
            {
                printf("%d. Date: %s, Time: %s, User: %s\n",
                    j + 1, (*(transports + i)).bookings[j].date,
                    (*(transports + i)).bookings[j].time, (*(transports + i)).bookings[j].user);  
            }


            printf("Enter booking number to edit: ");  
            scanf_s("%d", &booking_num);   
            while (getchar() != '\n');    

            if (booking_num < 1 || booking_num >(*(transports + i)).booking_count)  
            {
                printf("Invalid booking number\n");  
                return;                    
            }

            Booking* booking = &(*(transports + i)).bookings[booking_num - 1];  

            // Изменение даты бронирования
            do
            {
                printf("Enter new booking date (DD.MM.YYYY) [current: %s]: ", booking->date); 
        
                fgets(date_input, sizeof(date_input), stdin);  
                date_input[strcspn(date_input, "\n")] = '\0'; 

                if (strlen(date_input) == 0)   
                    break;

                FILE* fdate = NULL;           
                if (tmpfile_s(&fdate) != 0 || fdate == NULL)  
                {
                    printf("Temporary file error\n");  
                    return;
                }
                fputs(date_input, fdate);    
                rewind(fdate);               

                if (fscanf_s(fdate, "%d.%d.%d", &day, &month, &year) != 3)  
                {
                    printf("Invalid date format\n");  
                    fclose(fdate);            
                    continue;                  
                }
                fclose(fdate);                 

                if (!isValidDate(day, month, year))  
                {
                    printf("Invalid date\n");  
                    continue;                  
                }

 
                sprintf_s(new_date, sizeof(new_date), "%02d.%02d.%04d", day, month, year);  

                int conflict = 0;              
                for (int j = 0; j < (*(transports + i)).booking_count; j++)  
                {
                    if (j != booking_num - 1 && strcmp((*(transports + i)).bookings[j].date, new_date) == 0)  
                    {
                        conflict = 1;         
                        break;
                    }
                }

                if (conflict)                 
                {
                    printf("Vehicle already booked on this date\n");  
                    continue;                 
                }

                strcpy_s(booking->date, sizeof(booking->date), new_date);  
                break;                        
            } while (1);

            // Изменение времени бронирования
            do
            {
                printf("Enter new booking time (HH:MM) [current: %s]: ", booking->time);  
               
                fgets(time_input, sizeof(time_input), stdin);  
                time_input[strcspn(time_input, "\n")] = '\0'; 

                if (strlen(time_input) == 0)  
                    break;

                FILE* ftime = NULL;          
                if (tmpfile_s(&ftime) != 0 || ftime == NULL) 
                {
                    printf("Temporary file error\n");  
                    return;
                }
                fputs(time_input, ftime);    
                rewind(ftime);               

                if (fscanf_s(ftime, "%d:%d", &hour, &minute) != 2)  
                {
                    printf("Invalid time format\n");  
                    fclose(ftime);               
                    continue;                   
                }
                fclose(ftime);                 

                if (!isValidTime(hour, minute))  
                {
                    printf("Invalid time\n");  
                    continue;                 
                }

 
                sprintf_s(new_time, sizeof(new_time), "%02d:%02d", hour, minute);  
                strcpy_s(booking->time, sizeof(booking->time), new_time);  
                break;                       
            } while (1);

     
            printf("Enter new user name [current: %s]: ", booking->user);  
            char user_input[MAX_STRING];  
            fgets(user_input, sizeof(user_input), stdin);  
            user_input[strcspn(user_input, "\n")] = '\0';

            if (strlen(user_input) > 0)     
            {
                strcpy_s(booking->user, sizeof(booking->user), user_input);  
            }

            printf("Booking updated successfully\n");  
            saveToFile();                   
            return;                        
        }
    }

    if (!found)                         
        printf("Vehicle not found!\n"); 
}

// Сохранение данных в файл
void saveToFile()
{
    FILE* file; 


    if (fopen_s(&file, FILENAME, "w") != 0 || file == NULL)
    {
        printf("Error opening file for writing\n"); 
        return; 
    }


    for (int i = 0; i < transport_count; i++)
    {

        fprintf(file, "%d %d %s %d %d %s %d\n",
            (*(transports + i)).id,
            (*(transports + i)).type,
            (*(transports + i)).model,
            (*(transports + i)).capacity,
            (*(transports + i)).available,
            (*(transports + i)).current_status,
            (*(transports + i)).booking_count);


        for (int j = 0; j < (*(transports + i)).booking_count; j++)
        {
            fprintf(file, "%s %s %s\n",
                (*(transports + i)).bookings[j].date,
                (*(transports + i)).bookings[j].time,
                (*(transports + i)).bookings[j].user);
        }
    }

    fclose(file); 
}

// Загрузка данных из файла
int loadFromFile(const char* filename)
{
    FILE* file;


    if (fopen_s(&file, filename, "r") != 0 || file == NULL)
    {
        printf("Error opening file %s\n", filename); 
        return 0; 
    }
        


    while (!feof(file))
    {
        Transport t = { 0 };            
        int booking_count = 0;          // Количество бронирований 


        if (fscanf_s(file, "%d %d %49s %d %d %49s %d\n",
            &t.id,
            (int*)&t.type,
            t.model, (unsigned)_countof(t.model),
            &t.capacity,
            &t.available,
            t.current_status, (unsigned)_countof(t.current_status),
            &booking_count) != 7)
        {
            break; 
        }

        t.booking_count = booking_count; 
        t.bookings = (Booking*)malloc(booking_count * sizeof(Booking)); 


        for (int i = 0; i < booking_count; i++)
        {
            if (fscanf_s(file, "%19s %9s %49[^\n]\n",
                t.bookings[i].date, (unsigned)_countof(t.bookings[i].date),
                t.bookings[i].time, (unsigned)_countof(t.bookings[i].time),
                t.bookings[i].user, (unsigned)_countof(t.bookings[i].user)) != 3)
            {
                break; 
            }
        }

        ensureCapacity(); 
        transports[transport_count++] = t; 
    }

    fclose(file); 
    validateTransportData(); 
    return 1; 
}

// Экспорт данных в текстовый файл
int loadFromExportFile()
{
    FILE* file;
    if (fopen_s(&file, EXPORT_FILE, "r") != 0 || file == NULL) 
    {
        printf("Error opening export file\n");
        return 0;
    }


    cleanupTransportSystem();
    TransportSystem();

    char line[512];
    Transport t = { 0 };
    int line_number = 0;
    int errors = 0;

    while (fgets(line, sizeof(line), file))
    {
        line_number++;


        for (char* p = line; *p; p++)
        {
            if ((unsigned char)*p < 32 && *p != '\n' && *p != '\r' && *p != '\t')
            {
                *p = ' '; 
            }
        }


        if (strlen(line) < 5) continue;

      
        if (strstr(line, "ID:"))
        {
            char type_str[20] = { 0 };
            char model[50] = { 0 };
            char status[50] = { 0 };
            int parsed = 0;

            parsed = sscanf_s(line,
                "ID: %d | Type: %19[^|] | Model: %49[^|] | Capacity: %d | Available: %d | Status: %49[^\n]",
                &t.id,
                type_str, (unsigned)_countof(type_str),
                model, (unsigned)_countof(model),
                &t.capacity,
                &t.available,
                status, (unsigned)_countof(status));

            if (parsed != 6)
            {
                printf("Warning: Invalid format at line %d (parsed %d fields)\n", line_number, parsed);
                errors++;
                continue;
            }

            // Очистка строк от пробелов
            trim(type_str);
            trim(model);
            trim(status);

            // Определение типа транспорта
            if (strcmp(type_str, "Truck") == 0)
            {
                t.type = TRUCK;
            }
            else if (strcmp(type_str, "Passenger") == 0)
            {
                t.type = PASSENGER;
            }
            else
            {
                printf("Warning: Unknown vehicle type '%s' at line %d\n", type_str, line_number);
                errors++;
                continue;
            }

            // Копирование данных
            strcpy_s(t.model, sizeof(t.model), model);
            strcpy_s(t.current_status, sizeof(t.current_status), status);
            t.booking_count = 0;
            t.bookings = NULL;

            ensureCapacity();
            transports[transport_count++] = t;
        }
    }

    fclose(file);

    if (errors > 0)
    {
        printf("Loaded %d vehicles with %d errors\n", transport_count, errors);
    }
    else
    {
        printf("Successfully loaded %d vehicles\n", transport_count);
    }

    return transport_count > 0;
}

// Функция для удаления пробелов в начале и конце строки
void trim(char* str)
{
    char* start = str;
    while (isspace((unsigned char)*start)) start++;

    char* end = str + strlen(str) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;

    memmove(str, start, end - start + 1);
    str[end - start + 1] = '\0';
}



// Экспорт данных во временный текстовый файл
void exportToTextFile()
{
    FILE* file; 


    if (fopen_s(&file, EXPORT_FILE, "w") != 0 || file == NULL)
    {
        printf("Error opening export file\n"); 
        return; 
    }


    for (int i = 0; i < transport_count; i++)
    {

        fprintf(file, "ID: %d | Type: %s | Model: %s | Capacity: %d | Available: %d | Status: %s\n",
            (*(transports + i)).id, 
            (*(transports + i)).type == TRUCK ? "Truck" : "Passenger", 
            (*(transports + i)).model, 
            (*(transports + i)).capacity, 
            (*(transports + i)).available, 
            (*(transports + i)).current_status); 


        for (int j = 0; j < (*(transports + i)).booking_count; j++)
        {

            fprintf(file, "  Booking %d: Date: %s, Time: %s, User: %s\n",j + 1, 
                (*(transports + i)).bookings[j].date, 
                (*(transports + i)).bookings[j].time, 
                (*(transports + i)).bookings[j].user); 
        }
    }

    fclose(file); 
    printf("Data exported to %s\n", EXPORT_FILE); 
}

// Добавление нового ТС
void addTransport()
{
    ensureCapacity(); 


    if (transport_count >= transport_capacity)
    {
        printf("Maximum number of transports reached\n");
        return; 
    }

    int type_input; // Переменная для выбора типа ввода

    while (1) 
    {
        printf("Select type (0 - Freight, 1 - Passenger, 2 - Load from file): "); 


        if (scanf_s("%d", &type_input) != 1)
        {
            printf("Input error! Please enter 0, 1, or 2.\n"); 
            while (getchar() != '\n'); 
            continue; 
        }

        if (type_input == 0 || type_input == 1) 
        {
            Transport t = { 0 }; 


            t.id = transport_count > 0 ? transports[transport_count - 1].id + 1 : 1;

            t.type = (TransportType)type_input; 
            t.booking_count = 0; 
            t.bookings = NULL; 

            // Ввод модели
            while (1)
            {
                printf("Enter model: "); 
                char model_input[MAX_STRING]; // Буфер для ввода модели
                while (getchar() != '\n'); 


                if (fgets(model_input, sizeof(model_input), stdin) == NULL)
                {
                    printf("Input error!\n"); 
                    continue; 
                }
                model_input[strcspn(model_input, "\n")] = '\0'; 

                if (strlen(model_input) == 0) 
                {
                    printf("Model cannot be empty\n"); 
                    continue; 
                }

                strcpy_s(t.model, sizeof(t.model), model_input); 
                break; 
            }

            // Ввод вместительности 
            while (1)
            {
                printf("Enter capacity: "); 


                if (scanf_s("%d", &t.capacity) != 1)
                {
                    printf("Capacity input error. Please enter an integer.\n"); 
                    while (getchar() != '\n');
                    continue; 
                }

                if (t.capacity < 0) 
                {
                    printf("Capacity cannot be negative\n"); 
                    continue; 
                }
                break; 
            }

            // Ввод количества ТС
            while (1)
            {
                printf("Enter number available: "); 


                if (scanf_s("%d", &t.available) != 1)
                {
                    printf("Availability input error. Please enter an integer.\n");
                    while (getchar() != '\n'); 
                    continue; 
                }

                if (t.available < 1) 
                {
                    printf("Quantity must be greater than 0\n"); 
                    continue; 
                }
                break;
            }

            strcpy_s(t.current_status, sizeof(t.current_status), "Available"); 

            transports[transport_count++] = t; 
            saveToFile(); 
            printf("Transport successfully added. ID: %d\n", t.id); 
            return; 
        }
        // Ввод с файла
        else if (type_input == 2) 
        {
            while (getchar() != '\n'); 

            char filename[MAX_STRING]; // Буфер для имени файла
            printf("Enter filename to load from: "); 

            if (fgets(filename, sizeof(filename), stdin) == NULL)
            {
                printf("Filename input error\n"); 
                continue; 
            }
            filename[strcspn(filename, "\n")] = '\0'; 


            if (strlen(filename) == 0)
            {
                strcpy_s(filename, sizeof(filename), "car.txt"); 
            }


            if (loadFromFile(filename))
            {
                printf("Data successfully loaded from file %s\n", filename); 
                return; 
            }
            else
            {
                printf("Error loading from file %s. Please try again.\n", filename); 
                continue; 
            }
        }
        else 
        {
            printf("Invalid type! Please enter 0, 1, or 2.\n"); 
        }
    }
}

// Обновление доступности ТС
void updateAvailability()
{
    char input[MAX_STRING];              // Буфер для ввода 
    int found = 0;                       // Флаг, найден ли транспорт
    int search_by_id = 0;                // Флаг: поиск по ID или по модели
    int id = 0;                          // Переменная для хранения ID 
    int new_available;                   // Новое количество доступных ТС

    printf("\nUpdate Availability\nEnter vehicle ID or model: "); 
    fgets(input, sizeof(input), stdin);                           
    input[strcspn(input, "\n")] = '\0';                            

    char* endptr;                       
    id = strtol(input, &endptr, 10);   
    if (*endptr == '\0') search_by_id = 1; 

    for (int i = 0; i < transport_count; i++)  
    {
        if ((search_by_id && (*(transports + i)).id == id) ||   
            (!search_by_id && strcmp((*(transports + i)).model, input) == 0)) 
        {
            found = 1;                   

            printf("Current availability: %d\n", (*(transports + i)).available);  
            printf("Enter new available quantity: ");                           
            if (scanf_s("%d", &new_available) != 1) 
            {             
                printf("Input error! Please enter an integer.\n");              
                while (getchar() != '\n');                                       
                return;                                                          
            }
            while (getchar() != '\n');                                           

            if (new_available < 0)       
            {
                printf("Quantity cannot be negative\n"); 
                return;                                  
            }

            (*(transports + i)).available = new_available;   


            if (new_available == 0)
            {
                strcpy_s((*(transports + i)).current_status, sizeof((*(transports + i)).current_status), "Unavailable");  
            }
            else if ((*(transports + i)).booking_count > 0)
            {
                strcpy_s((*(transports + i)).current_status, sizeof((*(transports + i)).current_status), "Booked");       
            }
            else
            {
                strcpy_s((*(transports + i)).current_status, sizeof((*(transports + i)).current_status), "Available");    
            }

            printf("Availability updated successfully\n");  
            saveToFile();                                     
            return;                                          
        }
    }

    if (!found) printf("Vehicle not found!\n"); 
}

// Проверка статуса ТС
void checkStatus()
{
    char input[MAX_STRING];               // Буфер для ввода 
    int found = 0;                        // Флаг, найден ли транспорт
    int search_by_id = 0;                 // Флаг поиска по ID или модели
    int id = 0;                          // Переменная для ID

    printf("\nCheck Status\nEnter vehicle ID or model: ");  
    fgets(input, sizeof(input), stdin);                      
    input[strcspn(input, "\n")] = '\0';                     

    char* endptr;                   
    id = strtol(input, &endptr, 10);   
    if (*endptr == '\0') search_by_id = 1;   

    for (int i = 0; i < transport_count; i++)  
    {
        if ((search_by_id && (*(transports + i)).id == id) ||  
            (!search_by_id && strcmp((*(transports + i)).model, input) == 0))   
        {
            found = 1;   


            printf("\nVehicle Information:\n");
            printf("ID: %d\n", (*(transports + i)).id);
            printf("Type: %s\n", (*(transports + i)).type == TRUCK ? "Truck" : "Passenger");
            printf("Model: %s\n", (*(transports + i)).model);
            printf("Capacity: %d\n", (*(transports + i)).capacity);
            printf("Available: %d\n", (*(transports + i)).available);
            printf("Status: %s\n", (*(transports + i)).current_status);

            if ((*(transports + i)).booking_count > 0)  
            {
                printf("\nBookings:\n");
                for (int j = 0; j < (*(transports + i)).booking_count; j++)
                {
                    printf("%d. Date: %s, Time: %s, User: %s\n",
                        j + 1, (*(transports + i)).bookings[j].date,
                        (*(transports + i)).bookings[j].time, (*(transports + i)).bookings[j].user);
                }
            }
            return;   
        }
    }

    if (!found) printf("Vehicle not found!\n");  
}

// Фильтр ТС
void filterTransport()
{
    int type_filter = -1;                       // Фильтр по типу
    char model_filter[MAX_STRING] = "";         // Фильтр по модели 
    int min_capacity = -1;                      // Минимальная вместимость
    char type_input[10];                        // Буфер для типа
    char capacity_input[10];                    // Буфер для минимальной вместимости
    int found = 0;                              // Счётчик найденных транспортов

    printf("\nFilter Vehicles\n");    

    printf("Enter type (0 - Truck, 1 - Passenger, Enter - any): ");  
    fgets(type_input, sizeof(type_input), stdin);                     
    type_input[strcspn(type_input, "\n")] = '\0';                     

    if (strlen(type_input) > 0)  
    {
        type_filter = atoi(type_input);    
        if (type_filter < 0 || type_filter > 1)  
        {
            printf("Invalid type, using any type\n"); 
            type_filter = -1;                          
        }
    }

    printf("Enter model to filter (Enter - any): ");  
    fgets(model_filter, sizeof(model_filter), stdin); 
    model_filter[strcspn(model_filter, "\n")] = '\0'; 


    printf("Enter minimum capacity (Enter - any): "); 
    fgets(capacity_input, sizeof(capacity_input), stdin); 
    capacity_input[strcspn(capacity_input, "\n")] = '\0'; 

    if (strlen(capacity_input) > 0)  
    {
        min_capacity = atoi(capacity_input);    
        if (min_capacity < 0)                    
        {
            printf("Invalid capacity, using any capacity\n"); 
            min_capacity = -1;                                 
        }
    }


    printf("\nFilter Results:\n");
    printf("ID  | Type       | Model                | Capacity | Available | Status\n");
    printf("----|------------|----------------------|----------|-----------|--------\n");


    for (int i = 0; i < transport_count; i++)  
    {

        if ((type_filter == -1 || (*(transports + i)).type == type_filter) &&
            (strlen(model_filter) == 0 || strstr((*(transports + i)).model, model_filter)) &&
            (min_capacity == -1 || (*(transports + i)).capacity >= min_capacity))
        {

            printf("%-3d | %-10s | %-20s | %8d | %9d | %s\n",
                (*(transports + i)).id,
                (*(transports + i)).type == TRUCK ? "Truck" : "Passenger",
                (*(transports + i)).model,
                (*(transports + i)).capacity,
                (*(transports + i)).available,
                (*(transports + i)).current_status);

            found++;  
        }
    }

    if (!found)    
    {
        printf("No vehicles match the filter criteria\n"); 
    }
}

// Подсчет доступных ТС на дату
void countAvailableByDate()
{
    int day, month, year;           // Переменные для дня, месяца и года
    char date_str[20];              // Буфер для даты
    int available_count = 0;        // Счётчик доступных транспортов

    printf("\nCount Available Vehicles by Date\n");  

    do {
        printf("Enter date (DD.MM.YYYY): ");          
        if (scanf_s("%d.%d.%d", &day, &month, &year) != 3)  
        {
            while (getchar() != '\n');     
            printf("Invalid date format\n"); 
            continue;                        
        }
        while (getchar() != '\n');         
    } while (!isValidDate(day, month, year)); 

    printf(date_str, "%02d.%02d.%04d", day, month, year);  


    for (int i = 0; i < transport_count; i++) 
    {

        if (isVehicleAvailable((*(transports + i)).id, date_str) && (*(transports + i)).available > 0)
        {
            available_count++;             
        }
    }

    printf("\nAvailable vehicles on %s: %d\n", date_str, available_count);  

    if (available_count > 0)             
    {

        printf("\nAvailable Vehicles:\n");
        printf("ID  | Type       | Model                | Capacity\n");
        printf("----|------------|----------------------|----------\n");

        for (int i = 0; i < transport_count; i++)  
        {

            if (isVehicleAvailable((*(transports + i)).id, date_str) && (*(transports + i)).available > 0)
            {
                printf("%-3d | %-10s | %-20s | %8d\n",
                    (*(transports + i)).id,
                    (*(transports + i)).type == TRUCK ? "Truck" : "Passenger",
                    (*(transports + i)).model,
                    (*(transports + i)).capacity);
            }
        }
    }
}


// Вывод статистики по ТС
void printStatistics()
{
    int total_vehicles = transport_count;               // Общее количество транспортных средств 
    int total_trucks = 0;                               // Счётчик грузовых ТС
    int total_passengers = 0;                           // Счётчик пассажирских ТС
    int total_available = 0;                            // Общее количество доступных ТС
    int total_booked = 0;                               // Общее количество бронирований
    int total_capacity = 0;                             // Общая вместимость 

    for (int i = 0; i < transport_count; i++)          
    {
        if ((*(transports + i)).type == TRUCK)         
        {
            total_trucks++;                             
        }
        else 
        {
            total_passengers++;                         
        }

        total_available += (*(transports + i)).available;              
        total_booked += (*(transports + i)).booking_count;             
        total_capacity += (*(transports + i)).capacity * (*(transports + i)).available;  
    }

    printf("\nTransport Statistics\n");                    
    printf("Total vehicles: %d\n", total_vehicles);       
    printf(" - Trucks: %d\n", total_trucks);               
    printf(" - Passenger vehicles: %d\n", total_passengers);
    printf("Total available vehicles: %d\n", total_available);
    printf("Total bookings: %d\n", total_booked);         
    printf("Total transport capacity: %d\n", total_capacity);

    if (total_vehicles > 0)                              
    {
        printf("Average capacity per vehicle: %.2f\n", (float)total_capacity / total_vehicles);
    }
}

void printTransports()
{
    printf("\nList of All Vehicles\n");                
    printf("ID  | Type       | Model                | Capacity | Available | Status      | Bookings\n");  
    printf("----|------------|----------------------|----------|-----------|-------------|---------\n");  

    for (int i = 0; i < transport_count; i++)               
    {
        printf("%-3d | %-10s | %-20s | %8d | %9d | %-11s | %d\n",  
            (*(transports + i)).id,                          
            (*(transports + i)).type == TRUCK ? "Truck" : "Passenger",  
            (*(transports + i)).model,                            
            (*(transports + i)).capacity,                         
            (*(transports + i)).available,                       
            (*(transports + i)).current_status,                   
            (*(transports + i)).booking_count);                  
    }
}

// Поиск ТС
void searchTransport()
{
    char input[MAX_STRING];                                   // Буфер для ввода 
    int found = 0;                                            // Флаг найденных бронирований
    int search_by_id = 0;                                     // Флаг поиска по ID 
    int id = 0;                                               // Переменная для хранения ID 

    printf("\nSearch Vehicle\nEnter ID or model: ");          
    fgets(input, sizeof(input), stdin);                        
    input[strcspn(input, "\n")] = '\0';                        

    char* endptr;                                              
    id = strtol(input, &endptr, 10);                           
    if (*endptr == '\0') search_by_id = 1;                    

    printf("\nSearch Results:\n");                             
    printf("ID  | Type       | Model                | Capacity | Available | Status\n"); 
    printf("----|------------|----------------------|----------|-----------|--------\n"); 

    for (int i = 0; i < transport_count; i++)                  
    {
        if ((search_by_id && (*(transports + i)).id == id) || 
            (!search_by_id && strstr((*(transports + i)).model, input))) 
        {

            printf("%-3d | %-10s | %-20s | %8d | %9d | %s\n",  
                (*(transports + i)).id,                         
                (*(transports + i)).type == TRUCK ? "Truck" : "Passenger", 
                (*(transports + i)).model,                     
                (*(transports + i)).capacity,                   
                (*(transports + i)).available,                  
                (*(transports + i)).current_status);             

            found++;                                           
        }
    }

    if (!found)                                               
    {
        printf("No vehicles found matching \"%s\"\n", input); 
    }
}

// Редактирование информации о ТС
void editTransport()
{
    char input[MAX_STRING];                                  // Буфер для ввода 
    int found = 0;                                           // Флаг найденного транспорта
    int search_by_id = 0;                                    // Флаг поиска по ID
    int id = 0;                                              // Переменная для ID
    int field;                                               // Переменная для выбора 
    int new_id;                                              // Переменная для нового Id
    int new_type;                                            // Переменная для нового типа
    char new_model[MAX_STRING];                              // Для хранения новой модели
    int new_capacity;                                        // Переменная для новой вместительности
    int new_available;                                       // Переменная для новой доступности
    char new_status[MAX_STRING];                             // Для нового статуса

    printf("\nEdit Vehicle\nEnter ID or model: ");            
    fgets(input, sizeof(input), stdin);                        
    input[strcspn(input, "\n")] = '\0';                       

    char* endptr;                                              
    id = strtol(input, &endptr, 10);                          
    if (*endptr == '\0') search_by_id = 1;                   

    for (int i = 0; i < transport_count; i++)                  
    {
        if ((search_by_id && (*(transports + i)).id == id) || 
            (!search_by_id && strcmp((*(transports + i)).model, input) == 0)) 
        {

            found = 1;                                         

            printf("\nCurrent Vehicle Information:\n");        
            printf("1. ID: %d\n", (*(transports + i)).id);
            printf("2. Type: %s\n", (*(transports + i)).type == TRUCK ? "Truck" : "Passenger");
            printf("3. Model: %s\n", (*(transports + i)).model);
            printf("4. Capacity: %d\n", (*(transports + i)).capacity);
            printf("5. Available: %d\n", (*(transports + i)).available);
            printf("6. Status: %s\n", (*(transports + i)).current_status);

            printf("\nEnter field number to edit (1-6, 0 to cancel): ");  

            scanf_s("%d", &field);                                
            while (getchar() != '\n');                            

            if (field == 0)                                       
            {
                printf("Edit cancelled\n");                       
                return;                                          
            }

            switch (field)                                       
            {
            case 1:                                            
            {
                printf("Enter new ID: ");                       

                scanf_s("%d", &new_id);                         
                while (getchar() != '\n');                    


                for (int j = 0; j < transport_count; j++)
                {
                    if (j != i && (*(transports +j)).id == new_id)
                    {
                        printf("ID %d already exists\n", new_id);
                        return;                                 
                    }
                }

                (*(transports + i)).id = new_id;                
                break;
            }
            case 2:                                            
            {
                printf("Enter new type (0 - Truck, 1 - Passenger): "); 

                scanf_s("%d", &new_type);                       
                while (getchar() != '\n');                     

                if (new_type == 0 || new_type == 1)             
                {
                    (*(transports + i)).type = (TransportType)new_type; 
                }
                else
                {
                    printf("Invalid type\n");                   
                    return;                                     
                }
                break;
            }
            case 3:                                            
            {
                printf("Enter new model: ");                    

                fgets(new_model, sizeof(new_model), stdin);     
                new_model[strcspn(new_model, "\n")] = '\0';    

                if (strlen(new_model) > 0)                       
                {
                    strcpy_s((*(transports + i)).model, new_model); 
                }
                else 
                {
                    printf("Model cannot be empty\n");          
                    return;                                      
                }
                break;
            }
            case 4:                                           
            {
                printf("Enter new capacity: ");                 

                scanf_s("%d", &new_capacity);                    
                while (getchar() != '\n');                       

                if (new_capacity > 0)                            
                {
                    (*(transports + i)).capacity = new_capacity;
                }
                else 
                {
                    printf("Capacity must be positive\n");     
                    return;                                      
                }
                break;
            }
            case 5:                                            
            {
                printf("Enter new available count: ");         

                scanf_s("%d", &new_available);                   
                while (getchar() != '\n');                       

                if (new_available >= 0 && new_available <= (*(transports + i)).capacity) 
                {
                    (*(transports + i)).available = new_available;
                }
                else 
                {
                    printf("Available must be between 0 and capacity\n"); 
                    return;
                }
                break;
            }
            case 6:                                            
            {
                printf("Enter new status: ");                   

                fgets(new_status, sizeof(new_status), stdin);   
                new_status[strcspn(new_status, "\n")] = '\0';  

                if (strlen(new_status) > 0)                      
                {
                    strcpy_s((*(transports + i)).current_status, new_status); 
                }
                else 
                {
                    printf("Status cannot be empty\n");         
                    return;
                }
                break;
            }
            default:                                           
                printf("Invalid field number\n");               
                return;                                         
            }

            printf("Vehicle updated successfully\n");           
            return;                                             
        }
    }

    if (!found)                                                
    {
        printf("Vehicle not found\n");                         
    }
}

// Удаление ТС
void deleteTransport()
{
    char input[MAX_STRING];              // Буфер для ввода 
    int found = 0;                       // Флаг, найдено ли ТС
    int search_by_id = 0;                // Флаг, поиск пр Id
    int id = 0;                          // Переменная для хранения ID
    char confirm;                        // Переменная для ответа пользователя

    printf("\nDelete Vehicle\nEnter ID or model: "); 
    fgets(input, sizeof(input), stdin);               
    input[strcspn(input, "\n")] = '\0';               

    char* endptr;                                   
    id = strtol(input, &endptr, 10);                 
    if (*endptr == '\0') search_by_id = 1;           

    for (int i = 0; i < transport_count; i++)         
    {
        if ((search_by_id && (*(transports + i)).id == id) ||       
            (!search_by_id && strcmp((*(transports + i)).model, input) == 0)) 
        {
            found = 1;                              

            printf("\nVehicle to Delete:\n");      
            printf("ID: %d\n", (*(transports + i)).id);
            printf("Type: %s\n", (*(transports + i)).type == TRUCK ? "Truck" : "Passenger"); 
            printf("Model: %s\n", (*(transports + i)).model);
            printf("Capacity: %d\n", (*(transports + i)).capacity);
            printf("Available: %d\n", (*(transports + i)).available);
            printf("Status: %s\n", (*(transports + i)).current_status);

            if ((*(transports + i)).booking_count > 0)   
            {
                printf("\nWARNING: This vehicle has %d active bookings!\n", (*(transports + i)).booking_count); 
            }

            printf("\nAre you sure you want to delete this vehicle? (y/n): "); 

            scanf_s(" %c", &confirm);               
            while (getchar() != '\n');              

            if (tolower(confirm) != 'y')             
            {
                printf("Deletion cancelled\n");     
                return;                            
            }

            if ((*(transports + i)).bookings)
            {
                free((*(transports + i)).bookings);
            }

            for (int j = i; j < transport_count - 1; j++)
            {
                (*(transports + j)) = (*(transports + j + 1));   
            }

            transport_count--;                      

            printf("Vehicle deleted successfully\n"); 
            saveToFile();                         
            return;                             
        }
    }

    if (!found) printf("Vehicle not found!\n");     
}
